/**
 * @file icono.cpp
 * @brief Programa que genera una imagen de un tamaño muy reducido a partir de una imagen original.
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
    Image nueva; // Será la nueva imagen (icono de la original)

    // Comprobar validez de la llamada
    if (argc != 4){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: negativo <FichImagenOriginal> <FichImagenDestino> <Factor> \n";
        exit (1);
    }

    // Obtener argumentos
    origen  = argv[1];
    destino = argv[2];
    // Argumento Factor
    int factor = atoi(argv[3]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Factor de reducción: " << factor << endl;

    // Leer la imagen del fichero de entrada
    if(!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "(Imagen original)   = " << image.get_rows()  << " filas x " << image.get_cols() << " columnas " << endl;

    // ////////////////////// //
    // LLAMAR AL MÉTODO ICONO //
    // ////////////////////// //

    if(factor>0){

        // Si los parámetros son válidos para recortar la imagen, ejecutamos Crop
        nueva = image.Subsample(factor);

    }else{
        cout << endl << "////////////////////////////////////" << endl;
        cout << "ERROR EN EL PASO DE PARÁMETROS" << endl
             << "EL FACTOR DE REDUCCIÓN DEBE SER > 0" << endl;

        cout << "////////////////////////////////////" << endl << endl;


        cout << "Introduce un factor de reducción válido" << endl;

        return 1;
    }

    // ///////////////////// //

    // Dimensiones de "destino"
    cout << endl;
    cout << "Dimensiones de " << destino << ":" << endl;
    cout << "(Imagen icono) = " << nueva.get_rows() << " filas x " << nueva.get_cols() << " columnas" << endl;

    // Guardar la imagen resultado en el fichero
    if (nueva.Save(destino))
        cout  << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }
}