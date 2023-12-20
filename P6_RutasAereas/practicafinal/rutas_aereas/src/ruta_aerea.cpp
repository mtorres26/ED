/**
 * @file ruta_aerea.cpp
 * @brief Archivo de prueba final
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include "almacen_rutas.h"
#include "paises.h"
#include "imagen.h"
#include "imagenES.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

// //////////// //
// FUNCIÓN ROTA //
// //////////// //

Imagen Rota(const Imagen & Io,double angulo){
    double rads=angulo;
    double coseno = cos(angulo);
    double seno = sin(angulo);
    //Para obtener las dimensiones de la imagen
    int rcorners[4],ccorners[4];
    int newimgrows,newimgcols;
    double new_row_min,new_col_min,new_row_max,new_col_max;
    double inter,inter1;
    rcorners[0]=0;
    rcorners[1]=0;
    ccorners[0]=0;
    ccorners[2]=0;
    rcorners[2]=Io.GetFilas()-1;
    rcorners[3]=Io.GetFilas()-1;
    ccorners[1]=Io.GetFilas()-1;
    ccorners[3]=Io.GetFilas()-1;
    new_row_min=0;
    new_col_min=0;
    new_row_max=0;
    new_col_max=0;
    newimgrows=0;
    newimgcols=0;

    for(int count=0;count<4;count++){

        inter=rcorners[count]*coseno+ccorners[count]*seno;

        if(inter<new_row_min)
            new_row_min=inter;
        if(inter>new_row_max)
            new_row_max=inter;
        inter1=-rcorners[count]*seno+ccorners[count]*coseno;

        if(inter1<new_col_min)
            new_col_min=inter1;
        if(inter1>new_col_max)
            new_col_max=inter1;
    }

    newimgrows=(unsigned)ceil((double)new_row_max-new_row_min);
    newimgcols=(unsigned)ceil((double)new_col_max-new_col_min);

    Imagen Iout(newimgrows,newimgcols);
    for(int rows=0;rows<newimgrows;rows++){
        for(int cols=0;cols<newimgcols;cols++){

            float oldrowcos=((float)rows+new_row_min)*cos(-rads);
            float oldrowsin=((float)rows+new_row_min)*sin(-rads);
            float oldcolcos=((float)cols+new_col_min)*cos(-rads);
            float oldcolsin=((float)cols+new_col_min)*sin(-rads);
            float old_row=oldrowcos+oldcolsin;
            float old_col=-oldrowsin+oldcolcos;

            old_row=ceil((double)old_row);
            old_col=ceil((double)old_col);

            if((old_row>=0)&&(old_row<Io.GetFilas())&& (old_col>=0)&&(old_col<Io.GetCols())){
                Iout(rows,cols)=Io(old_row,old_col);

            }else{
                Iout(rows,cols).r=Iout(rows,cols).g=Iout(rows,cols).b=255;
                Iout(rows,cols).transp=0;
            }
        }
    }
    return Iout;
}

// ////////////// //
// FUNCIÓN PINTAR //
// ////////////// //

void Pintar( int f1,int f2,int c1,int c2,Imagen &I, const Imagen &avion,int mindisf,int mindisc){

    int fila,col;
    if (abs(f2-f1)>=mindisf || abs(c2-c1)>=mindisc){

        if (c1!=c2){
            double a,b;
            a= double(f2-f1)/double(c2-c1);
            b= f1-a*c1;
            col = (int)(c1+c2)/2;
            fila = (int)rint(a*col+b);
        }
        else{
            col = c1;
            fila = (f1+f2)/2;
        }


        double angulo = atan2((f2-f1),(c2-c1));
        Imagen Irota=Rota(avion,angulo+135);

        I.PutImagen(fila,col,Irota);//pensar si debe ser opaco o blending

        angulo = atan2((f2-fila),(c2-col));
        Irota=Rota(avion,angulo+135);

        I.PutImagen(f2,c2,Irota);//pensar si debe ser opaco o blending
        angulo = atan2((fila-f1),(col-c1));
        Irota=Rota(avion,angulo+135);

        I.PutImagen(f1,c1,Irota);//pensar si debe ser opaco o blending
    }
}

int main(int argc, char * argv[]) {

    // Comprobación de parámetros
    if (argc != 7) {
        cout << "Los parametros son:" << endl;
        cout << "1.-Fichero con la informacion de los paises" << endl;
        cout << "2.-Nombre de la imagen con el mapa del mundo" << endl;
        cout << "3.-Directorio con las banderas" << endl;
        cout << "4.-Fichero con el almacen de rutas" << endl;
        cout << "5.- Nombre de la imagen con el avion" << endl;
        cout << "6.- Nombre de la imagen de la mascara del avion" << endl;

        return 0;
    }


    // ///////////// //
    // PRUEBA PAISES //
    // ///////////// //

    cout << "- - - - - - - - " << endl << "- - PAISES - -" << endl << "- - - - - - - -" << endl;

    // Definimos un conjunto de Paises (compuesto por puntos)
    Paises Pses;

    // Leemos información sobre paises de un archivo y la insertamos en nuestro conjnuto Pses
    ifstream f(argv[1]);
    f >> Pses;

    // Mostramos la información sobre los paises:
    cout << endl << Pses;

    // /////////////// //
    // PRUEBA IMAGENES //
    // /////////////// //

    Imagen mapaMundi;
    mapaMundi.LeerImagen(argv[2]);

    //Leemos el avión que vamos a usar
    Imagen avion;
    avion.LeerImagen(argv[5], argv[6]);

    // //////////////////// //
    // PRUEBA ALMACÉN RUTAS //
    // //////////////////// //

    cout << endl << "- - - - - - - - - - -" << endl << "- - ALMACÉN RUTAS - -" << endl << "- - - - - - - - - - - "
         << endl;

    AlmacenRutas Ar;

    f.close();
    f.open(argv[4]);
    f >> Ar;

    cout << endl << "Las rutas son: " << endl << Ar;

    cout << endl << "Dime el codigo de una ruta --> " << endl;
    string cod_ruta;
    cin >> cod_ruta;
    Ruta R = Ar.getRuta(cod_ruta);

    // Comprobamos si la ruta pasada existe en nuestro almacén:

    // /////////// //
    // PRUEBA RUTA //
    // /////////// //

    cout << " - - - - - - -" << endl << " - - RUTA  - - " << endl << " - - - - - - -" << endl;

    AlmacenRutas::iterator it = Ar.find(R);

    if (it != Ar.end()) {
        cout << "La ruta que has solicitado tiene las siguientes características: " << endl;
        cout << "CODIGO --> " << R.getCodigoRuta() << endl;
        cout << "NUMERO DE RUTAS --> " << R.getPuntosRuta().size() << endl;

        int contador = 1;

        cout << "LOS SIGUIENTES PUNTOS: " << endl;

        R.muestraPuntos();

    } else {
        cout << "La ruta que has solicitado no existe, o el código es incorrecto." << endl;
    }

    // ///////////////////// //
    // PROGRAMA RUTAS AÉREAS //
    // ///////////////////// //

    cout << " - - - - - - - - -" << endl << " - - RUTAAÉREA - - " << endl << " - - - - - - - - -" << endl;


    Ruta::iterator punto_inicio = R.begin();
    Paises::iterator it_inicio = Pses.find(*punto_inicio);

    cout << "-Atravesaremos " << R.getPuntosRuta().size() << " países para llegar a nuestro destino --> " << endl;

    cout << "INICIAMOS la ruta en " << (*it_inicio).GetPais() << endl;

    // Seguiremos el pseudocódigo proporcionado:

    // 0) Declaramos los iteradores y variables que nos ayudarán al desarrollo durante la iteración sobre rutas:

    // 'it_punto_actual' apuntará al punto actual de la ruta
    // 'it_punto_siguiente' apuntará al siguiente punto de la ruta
    Ruta::iterator it_punto_actual;
    Ruta::iterator it_punto_siguiente;

    // it_pais_actual apuntará al país actual de la ruta
    // it_pais_siguiente apuntará al siguiente país de la ruta
    Paises::iterator it_pais_actual;
    Paises::iterator it_pais_siguiente;

    // Iteramos sobre la Ruta R:
    for (it_punto_actual = R.begin(); it_punto_actual != R.end(); ++it_punto_actual) {

        // Obtenemos el punto actual de la ruta
        Punto actual = (*it_punto_actual);

        // Obtenemos el siguiente punto de la ruta
        it_punto_siguiente = it_punto_actual;
        ++it_punto_siguiente; // No debería pasar nada mientras ot no sea R.end()
        Punto siguiente = (*it_punto_siguiente);

        // Encontramos los países correspondientes a los puntos "actual" y "siguiente"
        it_pais_actual = Pses.find(actual);
        it_pais_siguiente = Pses.find(siguiente);

        // Extraemos el nombre del país actuál
        string nombre_pais = argv[3] + (*it_pais_actual).GetBandera();

        // Leemos la bandera del país actual y la pintamos
        Imagen bandera;
        bandera.LeerImagen(nombre_pais.c_str(),"");

        // Imprimimos por pantalla el 'viaje' de país a país que realizamos
        if(it_pais_actual!=Pses.end() && it_pais_siguiente!=Pses.end()) {
            cout << "Viajamos de " << (*it_pais_actual).GetPais() << " a " << (*it_pais_siguiente).GetPais() << endl;
        }else if(it_pais_actual!=Pses.end() && it_pais_siguiente==Pses.end()){
            cout << "TERMINAMOS la ruta en " << (*it_pais_actual).GetPais() << endl;
        }

        // Construimos la imagen final pegando los paises correspondientes en las posiciones correspondientes
        // y rotando los aviones en la orientación adecuada.

        // Para ello seguiremos la descripción que observamos en la diapositiva 15/16 de Clase PPFinal.pptx
        // Sabemos que:
        //  -> columnas = longitud
        //  -> filas = latitud
        int longitud_actual = (int) ((mapaMundi.GetCols() / 360.0) * (180 + actual.getLongitud()));
        int latitud_actual = (int) ((mapaMundi.GetFilas() / 180.0) * (90 - actual.getLatitud()));

        // Mientras no nos encontremos en el último de los países, pintamos el avión en el país de destino
        // siguiendo la misma descripción en cuanto a la posición y rotación descrita
        if (it_pais_siguiente != Pses.end()) {

            int longitud_siguiente = (int) ((mapaMundi.GetCols() / 360.0) * (180 + (*it_punto_siguiente).getLongitud()));
            int latitud_siguiente = (int) ((mapaMundi.GetFilas() / 180.0) * (90 - (*it_punto_siguiente).getLatitud()));

            // Pintamos los aviones utilizando el método "Pintar" ya proporcionado
            // ¿Qué representan mindisf y mindsc? ¿Mínima distancia filas?¿Para qué?
            // En el método Pintar hemos añadido +135º a cada ángulo para que los aviones
            // salgan con la orientación correcta
            Pintar(latitud_siguiente - avion.GetFilas(), latitud_actual - avion.GetFilas(), longitud_siguiente - avion.GetCols(),longitud_actual - avion.GetCols(), mapaMundi, avion, 0, 0);
        }

        // Pintaremos la bandera después pintar el avión en la posición correcta
        mapaMundi.PutImagen(latitud_actual - bandera.GetFilas(), longitud_actual - bandera.GetCols(), bandera, BLENDING);
    }

    cout << endl << "Observa la imagen que encontrarás en: /practicafinal, con nombre (" <<
    cod_ruta+".ppm" << ") para ver el recorrido del avión por el mapa." << endl;

    // Finalmente, escribimos la imagen:
    mapaMundi.EscribirImagen((cod_ruta+".ppm").c_str());
}
