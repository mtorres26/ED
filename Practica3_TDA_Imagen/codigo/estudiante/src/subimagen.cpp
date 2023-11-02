/**
 * @file subimagen.cpp
 * @brief Programa que genera una imagen de tamaño menor o igual que la original.
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
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino> <fila> <col> <lado>\n";
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
    // LLAMAR AL MÉTODO CROP //
    // ///////////////////// //

    // Primero almacenamos los nuevos parámetros de entrada que necesita crop
    int fila = atoi(argv[3]);
    int columna = atoi(argv[4]);
    int num_filas = atoi(argv[5]);
    int num_columnas = atoi(argv[6]);

    // Comprobaremos que los parámetros pasados son válidos para realizar el recorte:
    if((fila>=0 && fila<=image.get_rows())&&(columna>=0 && columna)&&(fila+num_filas<=image.get_rows())&&((columna+num_columnas)<=image.get_cols())){

        // Si los parámetros son válidos para recortar la imagen, ejecutamos Crop
        nueva = image.Crop(fila,columna,num_filas,num_columnas);

    }else{
        cout << endl << "//////////////////////////////////////////////////////////////" << endl;
        cout << "ERROR EN EL PASO DE PARÁMETROS" << endl
             << "LOS PARÁMETROS DEBEN AJUSTARSE AL TAMAÑO DE LA IMAGEN ORIGINAL" << endl;

        cout << "//////////////////////////////////////////////////////////////" << endl << endl;


        cout << "Fila -> Entre 0 y " << image.get_rows() << endl
             << "Columna -> Entre 0 y " << image.get_cols() << endl
             << "Num_filas --> Fila + num_filas deberá ser menor que " << image.get_rows() << endl
             << "Num_columnas --> Columna + num_columnas deberá ser menor que " << image.get_cols() << endl;

        return 1;
    }


    // ///////////////////// //

    // Dimensiones de "destino"
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "(Imagen recortada) = " << nueva.get_rows() << " filas x " << nueva.get_cols() << " columnas" << endl;

    // Guardar la imagen resultado en el fichero
    if (nueva.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}