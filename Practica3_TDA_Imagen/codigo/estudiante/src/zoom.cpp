/**
 * @file zoom.cpp
 * @brief Programa que genera una imagen ampliada de la original.
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
    Image nueva; // Será la nueva imagen (recortada de la original)

    // Comprobar validez de la llamada
    if (argc != 6){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino>\n";
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
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "(Imagen original)   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // ///////////////////// //
    // LLAMAR AL MÉTODO ZOOM //
    // ///////////////////// //

    // Primero almacenamos los nuevos parámetros de entrada que necesita ZOOM

    // fila y columna representan la coordenada de la esquina superior izquierda
    // a partir de la cuál extraemos la subimagen
    int fila = atoi(argv[3]);
    int col = atoi(argv[4]);
    // lado representa el tamaño del lado del cuadrado (deberá estar totalmente incluído en la imagen)
    int lado = atoi(argv[5]);

    // Comprobación de parámetros
    if(((fila>=0 && fila<=image.get_rows())&&(col>=0 && col)) && ( (fila+lado)<=image.get_rows() && (col+lado)<=image.get_cols())  ){

        // El cuadrado está contenido dentro de la imagen, y las coordenadas son válidas para hacer el zoom
        nueva = image.Zoom2X(fila,col,lado);

    }else{

        cout << "// ////////////////////////////////////////////////////////////// //" << endl;
        cout << "// ERROR EN EL PASO DE PARÁMETROS                                 //" << endl
             << "// LOS PARÁMETROS DEBEN AJUSTARSE AL TAMAÑO DE LA IMAGEN ORIGINAL //" << endl;
        cout << "///////////////////////////////////////////////////////////////// //" << endl << endl;


        cout << "Fila -> Entre 0 y " << image.get_rows() << endl
             << "Columna -> Entre 0 y " << image.get_cols() << endl
             << "Lado --> 'Fila' + 'lado' deberá ser menor que " << image.get_rows() << endl
             << "y Num_columnas --> 'Columna' + 'lado' deberá ser menor que " << image.get_cols() << endl;


        return -1;
    }


    // ///////////////////// //

    // Dimensiones de "destino"
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "(Imagen con Zoom) = " << nueva.get_rows() << " filas x " << nueva.get_cols() << " columnas" << endl;

    // Guardar la imagen resultado en el fichero
    if (nueva.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}