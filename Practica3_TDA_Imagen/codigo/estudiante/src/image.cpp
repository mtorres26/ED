/**
 * @file image.cpp
 * @brief Fichero con definiciones para los métodos primitivos de la clase Image
 *
 */

#include <cstring>
#include <cassert>
#include <iostream>

#include <image.h>
#include <imageIO.h>

#include <cmath>

using namespace std;

/********************************
      FUNCIONES PRIVADAS
********************************/
void Image::Allocate(int nrows, int ncols, byte * buffer){
    rows = nrows;
    cols = ncols;

    img = new byte * [rows];

    if (buffer != 0)
        img[0] = buffer;
    else
        img[0] = new byte [rows * cols];

    for (int i=1; i < rows; i++)
        img[i] = img[i-1] + cols;
}

// Función auxiliar para inicializar imágenes con valores por defecto o a partir de un buffer de datos
void Image::Initialize (int nrows, int ncols, byte * buffer){
    if ((nrows == 0) || (ncols == 0)){
        rows = cols = 0;
        img = 0;
    }
    else Allocate(nrows, ncols, buffer);
}

// Función auxiliar para copiar objetos Imagen

void Image::Copy(const Image & orig){
    Initialize(orig.rows,orig.cols);
    for (int k=0; k<rows*cols;k++)
        set_pixel(k,orig.get_pixel(k));
}

// Función auxiliar para destruir objetos Imagen
bool Image::Empty() const{
    return (rows == 0) || (cols == 0);
}

void Image::Destroy(){
    if (!Empty()){
        delete [] img[0];
        delete [] img;
    }
}

LoadResult Image::LoadFromPGM(const char * file_path){
    if (ReadImageKind(file_path) != IMG_PGM)
        return LoadResult::NOT_PGM;

    byte * buffer = ReadPGMImage(file_path, rows, cols);
    if (!buffer)
        return LoadResult::READING_ERROR;

    Initialize(rows, cols, buffer);
    return LoadResult::SUCCESS;
}

/********************************
       FUNCIONES PÚBLICAS
********************************/

// Constructor por defecto

Image::Image(){
    Initialize();
}

// Constructores con parámetros
Image::Image (int nrows, int ncols, byte value){
    Initialize(nrows, ncols);
    for (int k=0; k<rows*cols; k++) set_pixel(k,value);
}

bool Image::Load (const char * file_path) {
    Destroy();
    return LoadFromPGM(file_path) == LoadResult::SUCCESS;
}

// Constructor de copias

Image::Image (const Image & orig){
    assert (this != &orig);
    Copy(orig);
}

// Destructor

Image::~Image(){
    Destroy();
}

// Operador de Asignación

Image & Image::operator= (const Image & orig){
    if (this != &orig){
        Destroy();
        Copy(orig);
    }
    return *this;
}

// Métodos de acceso a los campos de la clase

int Image::get_rows() const {
    return rows;
}

int Image::get_cols() const {
    return cols;
}

void Image::Invert() {
    for(int i = 0; i < this->size(); i++){
        this->set_pixel(i,255-this->get_pixel(i));
    }
}

int Image::size() const{
    return get_rows()*get_cols();
}

// Métodos básicos de edición de imágenes
void Image::set_pixel (int i, int j, byte value) {
    img[i][j] = value;
}
byte Image::get_pixel (int i, int j) const {
    return img[i][j];
}

// This doesn't work if representation changes
void Image::set_pixel (int k, byte value) {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse set_pixel(i,j,value)?
    img[0][k] = value;
}

// This doesn't work if representation changes
byte Image::get_pixel (int k) const {
    // TODO this makes assumptions about the internal representation
    // TODO Can you reuse get_pixel(i,j)?
    return img[0][k];
}

// Métodos para almacenar y cargar imagenes en disco
bool Image::Save (const char * file_path) const {
    // TODO this makes assumptions about the internal representation
    byte * p = img[0];
    return WritePGMImage(file_path, p, rows, cols);
}


// Método para generar una subimagen
Image Image::Crop(int nrow, int ncol, int height, int width) const {

    Image nueva_imagen(height, width);

    // nrow --> Fila en la que queremos empezar el recorte
    // ncol --> Columna en la que queremos empezar el recorte
    // height --> Nº filas que tendrá el recorte
    // width --> Nº columnas que tendrá el recorte

    /*
        Recorremos la nueva imagen que queremos con las dimensiones height y width
        y establecemos como nuevo valor del pixel de nuestra celda, el correspondiente
        a la imagen con la que estamos trabajando.
    */

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            nueva_imagen.set_pixel(i, j, this->get_pixel(nrow + i, ncol + j));
        }
    }
    return nueva_imagen;
}

// Método para ampliar un imagen x2
Image Image::Zoom2X(int nrow, int ncol, int height, int width) const {
    Image imagen2x((2*height-1), (2*width-1));

    //Misma comprobación que en crop
    if((nrow >= 0 && nrow < this->rows) && (ncol >= 0 && nrow < this->cols)){
        if(nrow+height < this->rows && ncol+width < this->cols){
            // Bucle for para inicializar los valores de la nueva imagen con los de la anterior
            for(int i = 0; i < imagen2x.get_rows(); i++) {
                for (int j = 0; j < imagen2x.get_cols() - 1; j++) {
                    //Para que no se salte la primera columna compruebo que sea 0 y añado los pixeles en esa columna
                    if (j == 0) {
                        //nrow + i/2 y ncol + j/2 para que no llegue al doble en la imagen original
                        imagen2x.set_pixel(i, j, this->get_pixel(nrow + i/2, ncol + j/2));
                    }else{
                        imagen2x.set_pixel(i, j +1, this->get_pixel(nrow + i/2, ncol + j/2));
                    }
                }
            }
            //Interpolo por filas y por columnas
            imagen2x.interpolarCol();
            imagen2x.interpolarFil();
        }
        else{
            //Que devuelva un error si falla la comprobación del principio
            cerr <<"Error";
            exit(1);
        }
    }
    else{
        //Que devuelva un error si falla la comprobación del principio
        cerr <<"Error";
        exit(1);
    }
    //Devuelvo la nueva imagen
    return imagen2x;
}

void Image::interpolarCol() {
    byte interpolacion;

    for(int i = 0; i < this->rows; i++){
        for(int j = 0; j < this->cols-2; j++){
            interpolacion = (byte)((img[i][j] + img[i][j+2])/2);
            img[i][j+1] = interpolacion;
        }
    }
}
void Image::interpolarFil() {
    byte interpolacion;

    for(int i = 0; i < this->rows-2; i++){
        for(int j = 0; j < this->cols; j++){
            interpolacion = (byte)((img[i][j] + img[i+2][j])/2);
            img[i+1][j] = interpolacion;
        }
    }
}

// Método para crear un icono a partir de una imagen
Image Image::Subsample(int factor) const{
    // Creamos nueva imagen sabiendo que: La imagen resultante tendrá floor(filas/factor) x floor(cols/factor) de dimensiones
    // Floor es una función que redondea hacia abajo
    Image nueva_imagen(floor(this->get_rows() / factor), floor(this->get_cols() / factor));

    float suma;
    float media=0;
    float divisor=factor*factor; // Si el factor es 2x2, para hacer la media de valores que nos de el nuevo valor del pixel, divideremos entre 4.

    // i y j iterarán sobre la nueva imagen.
    for (int i = 0; i < nueva_imagen.get_rows(); i++) {
        for (int j = 0; j < nueva_imagen.get_cols(); j++) { // Recorremos cada celda de la nueva imagen
            suma = 0; // Suma será el valor que tomará cada celda tras calcular la media de todas las subceldas de la imagen origal, por eso lo inicializamos a 0 cada vez que saltamos a otra celda.

            // k y p iterarán sobre la imagen original.
            for (int k = 0; k < factor; k++) {
                for (int p = 0; p < factor; p++) {
                    // Sacamos la suma de valores de la subseccion de la imagen original
                    int fila=k+factor*i;
                    int col=p+factor*j;
                    suma = suma + get_pixel(fila,col);
                }
            }
            media = suma / (float)(divisor); // Lo del float es para los decimales.
            // El nuevo valor del pixel de la nueva imagen en la posicion [i][j] será "media".
            nueva_imagen.set_pixel(i, j, (byte)roundf(media)); // El roundf es por si media=8.6 , para que lo redondee a 9.
        }
    }

    return nueva_imagen;
}

// Método para aumentar el contraste de una imagen mediante un estiramiento del histograma

void Image::AdjustContrast (byte in1, byte in2, byte out1, byte out2){

    float a, b, min, max; // a=in1 // b=in2 // min=out1 // max=out2

    byte const MIN = 0; // Valor mínimo de la cota inferior
    byte const MAX = 255; // Valor máximo de la cota superior

    float cociente; // Es la parte constante de la ecuacion E1.
    float valor; // Valor que tendrá el nuevo pixel con el contraste cambiado.

    byte pixel; // Contendrá el valor de "z"

    for(int i=0;i<this->rows;i++){
        for(int j=0;j<this->cols;j++){
            pixel = this->get_pixel(i,j); // Esto nos dará el valor del pixel "z"
            // Ahora debemos comprobar en qué rango de valores se encuentra:
            if(MIN <= pixel <= in1){ // Si está entre 0 y e1 --> Pasará a estar entre 0 y s1=min=out1

                a=(float)MIN;
                min=(float)MIN;
                b=(float)in1;
                max=(float)out1;

                cociente=(max-min)/(b-a);
                valor = roundf(min + (cociente * ( (float)pixel) - a));
                pixel = (byte)valor;
                this->set_pixel(i,j,pixel);

            }else if(in1 <= pixel <= in2){ // Si está entre e1 y e2 --> Pasará a estar entre s1=min=out1 y s2=max=out2
                a=(float)in1;
                min=(float)out1;
                b=(float)in2;
                max=(float)out2;

                cociente=(max-min)/(b-a);
                valor = roundf(min + (cociente * ( (float)pixel) - a));
                pixel = (byte)valor;
                this->set_pixel(i,j,pixel);

            }else if(in2 <= pixel <= MAX){ // Si está entre e2 y e255 --> Pasará a estar entre s2=max=out2 y 255
                a = (float)in2;
                min = (float)out2;
                b = (float)MAX;
                max = (float)MAX;

                cociente=(max-min)/(b-a);
                valor = roundf(min + (cociente * ( (float)pixel) - a));
                pixel = (byte)valor;
                this->set_pixel(i,j,pixel);
            }
        }
    }
}

// Método para barajar las filas de una imagen.
void Image::ShuffleRows() {
    const int p = 9973;
    Image temp(rows,cols);
    int newr;
    for (int r=0; r<rows; r++){
        newr = r*p % rows;
        for (int c=0; c<cols;c++)
            temp.set_pixel(r,c,get_pixel(newr,c));
    }
    Copy(temp);
}