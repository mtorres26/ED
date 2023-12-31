/**
 * @file barajar.cpp
 * @brief Programa que genera una imagen con las filas de píxeles barajadas con respecto de la imagen original.
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */
#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include <imageIO.h>

using namespace std;

int main(int argc, char *argv[]){
    char *origen, *destino; // nombres de los ficheros
    Image image;
    Image new_imagen;

    // Comprobar validez de la llamada
    if (argc != 3){
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
    //cout << "Fichero resultado: " << destino << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;


    image.ShuffleRows();
/*
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "   Imagen   = " << new_imagen.get_rows()  << " filas x " << new_imagen.get_cols() << " columnas " << endl;

    // Guardar la imagen resultado en el fichero
    if (new_imagen.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
*/
    if (image.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
    return 0;
}