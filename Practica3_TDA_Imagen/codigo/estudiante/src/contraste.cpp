/**
 * @file contraste.cpp
 * @brief Programa que genera una imagen de niveles de gris con más contraste que la original.
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */
#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main (int argc, char *argv[]){
    char *origen, *destino; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino> <in1> <in2> <out1> <out2> \n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if(!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "Imagen original   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // /////////////////////////////// //
    // LLAMAR AL MÉTODO ADJUSTCONTRAST //
    // /////////////////////////////// //

    // Leemos los argumentos

    int in1 = atoi(argv[3]);
    int in2 = atoi(argv[4]);
    int out1 = atoi(argv[5]);
    int out2 = atoi(argv[6]);

    cout << endl << "Comprobación de paso de argumentos: ";

    // Comprobamos que los argumentos pasados son correctos y ejecutamos en caso de que lo sean
    if( (0<=in1<=255) && (0<=in2<=255) && (0<=out1<=255) && (0<=out2<=255) ) {
        cout << endl << "BIEN: Umbrales en el rango correcto: 0<=umbral<=255 " << endl;

        if(in1 < in2) {
            cout << "BIEN: in1 < in2 " << endl;

            if(out1 < out2) {

                cout << "BIEN: out1 < out2 " << endl;
                cout << "Paso de argumentos correcto " << endl;
                image.AdjustContrast(in1,in2,out1,out2);

            }else {
                cout << "MAL: out1 < out2" << endl;
                return 1;
            }

        }else {
            cout << "MAL: in1 < in2" << endl;
            return 1;
        }

    }else {

        cout << "Umbrales en el rango incorrecto: 0<=umbral<=255 " << endl;
        return 1;
    }



    // ///////////////////// //

    // Dimensiones de "destino"
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "Imagen con constraste modificado = " << image.get_rows() << " filas x " << image.get_cols() << " columnas" << endl;

    // Guardar la imagen resultado en el fichero
    if (image.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}