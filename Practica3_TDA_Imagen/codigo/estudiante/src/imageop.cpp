/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

#include <cassert>

using namespace std;

// Crop
Image Image::Crop(int nrow, int ncol, int height, int width) const {

    // Crearemos una imagen nueva con tamaño HEIGHT X WIDTH
    // Se llama al constructor con parámetros, cuyo parámetro "byte value"
    // es 0 por defecto como vemos en su definición en image.h
    Image nueva(height,width);


    // Establecemos pixel a pixel el valor de cada uno de los píxeles de nuestra 'nueva' imagen (representa el recorte)
    // a partir de la imagen 'original' (this), sólamente con las coordenadas pasadas como argumentos
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            nueva.set_pixel(i,j, this->get_pixel(nrow+i,ncol+j));
        }
    }

    return nueva;
}

void Image::Invert() {
    // Calcular el negativo
    for (int i = 0; i < this->size(); i++){
        this->set_pixel(i, 255 - this->get_pixel(i));
    }
}



// Zoom
Image Image::Zoom2X(int fil, int col, int lado) const {

    int tam = (lado * 2) - 1;
    Image nueva(tam, tam);


    int contador = 0;
    // Primero recorreré la imagen añadiendo los píxeles ya conocidos
    // Sabemos que se colocarán en las posiciones pares tanto para filas como para columnas
    for (int i = 0; i < nueva.get_rows(); i += 2) {
        for (int j = 0; j < nueva.get_cols(); j += 2) {
            nueva.set_pixel(i, j, this->get_pixel(fil+i/2,col+j/2));
            contador++;
        }
    }


    // Ahora ya tenemos los ṕixeles conocidos colocados.
    // EJEMPLO:

    /*  0  1  2  3  4
       --------------
     0| 10 X  6  X  10
     1| X  X  X  X  X
     2| 8  X  9  X  6
     3| X  X  X  X  X
     4| 9  X  10 X  10
       ----------------
     */

    byte media, filPar, colPar;
    // Iremos pixel a pixel añadiendo el resto a partir de los ya conocidos
    // en función de la posición (fil,col) de cada uno de los píxeles que vamos a calcular
    for (int i = 0; i < nueva.get_rows(); i++) {
        for (int j = 0; j < nueva.get_cols(); j++) {
            if (i % 2 != 0 && j % 2 != 0) { // Fila y Columna impar. MEDIA CON LOS VECINOS DE LAS DIAGONALES
                media = (byte) (((nueva.img[i - 1][j - 1]) + (nueva.img[i - 1][j + 1]) + (nueva.img[i + 1][j - 1]) +
                                 (nueva.img[i + 1][j + 1])) / 4);
                nueva.set_pixel(i, j, media);

            } else if ((i % 2 == 0 && j % 2 != 0)) { // Fila par y Columna impar // MEDIA CON LOS VECINOS A IZQUIERDA Y DERECHA
                filPar = (byte) (((nueva.img[i][j - 1]) + (nueva.img[i][j + 1])) / 2);
                nueva.set_pixel(i, j, filPar);

            } else if ((i % 2 != 0 && j % 2 == 0)) { // Fila impar y Columna par // MEDIA CON LOS VECINOS DE ARRIBA Y ABAJO
                colPar = (byte) (((nueva.img[i - 1][j]) + (nueva.img[i + 1][j])) / 2);
                nueva.set_pixel(i, j, colPar);
            }
        }
    }

    //nueva.imprimeBytes();

    return nueva;
}

// Icono
Image Image::Subsample(int factor) const{

    Image nueva(this->get_rows()/factor,this->get_cols()/factor);

    int denominador=factor*factor;
    int fila,col,suma=0;

    // "i" y "j" iterarán sobre la nueva imagen icono
    for(int i=0; i < nueva.get_rows();i++){
        for(int j=0; j < nueva.get_cols();j++){
            suma=0;

            // "k" y "z" iteran sobre la imagen original
            for(int k=0;k<factor;k++){
                for(int z=0;z<factor;z++){
                    // De esta forma iteraremos sobre los subsectores "factor x factor"
                    // de la imagen original
                    fila = k+factor*i;
                    col = z+factor*j;

                    suma+=(this->get_pixel(fila,col));
                }

            }

            suma=suma/denominador;
            nueva.set_pixel(i,j,(byte)(suma));
        }
    }

    return nueva;
}

// e1=a       e2=b    s1=min      s2=max
void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2) {

    double valor; // Será la z'
    double constante; // Representa el bloque de la ecuación que siempre se repite --> (max-min)/(b-a)

    byte pixel; // Almacenaremos cada pixel 'z' para su posterior conversión
    byte nuevo;

    double a,b,min,max;
    // Si pixel está en [0,in1] --> pixel=[0,out1]
    // Si pixel está en [out1,out2] --> pixel=[in1,in2]
    // Si pixel está en [in2,255] --> pixel=[out2,255]
    // valor = min + (constante*(pixel-a))

    for(int i=0;i<this->get_rows()*this->get_cols();i++){
        pixel=this->get_pixel(i);

        // En función del valor del pixel en el que nos encontremos (z),
        // para cada una de las posibilidades, obtendremos el valor de:
        // min,max,a,b
        if(0<=pixel && pixel<in1){ // [0,e1)=[0,in1) --> [0,s1)=[0,out1)
            min=0;
            max=(double)out1;
            a=0;
            b=(double)in1;

        }else if(in1<=pixel && pixel<=in2){ // [e1,e2]=[in1,in2] --> [s1,s2]=[out1,out2]
            min=(double)out1;
            max=(double)out2;
            a=(double)in1;
            b=(double)in2;

        }else if(in2<pixel && pixel<=255){ // (e2,255]=(in2,255] --> (s1,s2]=(out1,out2]
            min = (double)out2;
            max = 255;
            a = (double)in2;
            b = 255;
        }

        // (max-min)/(b-a)
        constante = ((max-min)/(b-a));
        // z' = min + [(constante) * (z-a)]
        valor = min + (constante*(double(pixel-a)));

        this->set_pixel(i,(unsigned char)round(valor));
    }
}

// EJERCICIO 5
/* IMPLEMENTACIÓN INICIAL
 *
 */
void Image::ShuffleRows() {
    const int p = 9973;
    // Creamos una imagen temporal del mismo tamaño que la invocadora del método
    Image temp(rows,cols);
    int newr; // Representará 'R' --> El nuevo índice de filas

    for(int r=0; r<rows; r++){
        // Por cada fila de nuestra imagen, calcularemos el nuevo índice de fila a partir
        // del algoritmo
        newr = r*p % rows;

        for(int c=0; c<cols;c++){
            // Para cada columna, estableceremos el pixel actual al correspondiente
            // al índice de fila nuevo, y la columna actual de nuestra imagen original
            temp.set_pixel(r,c, get_pixel(newr,c));
        }
    }

    // Copiamos 'temp' en nuestra imagen
    Copy(temp);
}

// MÉTODOS AUXILIARES

void Image::imprimeBytes() const{

    cout << "Tamaño imagen: " << this->size() << endl <<
         "Dimensiones: " << this->get_rows() << " x " << this->get_cols() << endl;

    int tam = this->size();

    cout << "IMPRIMO IMAGEN " << endl;

    for(int i=0;i<this->get_rows();i++){
        cout << endl;
        for(int j=0;j<this->get_cols();j++){
            cout << this->img[i][j] << " ";
        }
    }

}