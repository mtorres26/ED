/*!
 * @file image.h
 * @brief Cabecera para la clase Image
 */

#ifndef _IMAGEN_H_
#define _IMAGEN_H_


#include <cstdlib>
#include "imageIO.h"



typedef unsigned char byte;

enum LoadResult: unsigned char {
    SUCCESS,
    NOT_PGM,
    READING_ERROR
};


/**
  @brief T.D.A. Imagen

  Una instancia del tipo de dato abstracto Imagen nos permite almacenar imágenes de intensidades.

  El TDA Imagen proporciona además distintas herramientas para la manipulación de dichas imágenes.

  Para poder usar el TDA Imagen se debe incluir el fichero

  \#include <Imagen.h>

  @author Alberto Ortega Vilchez
  @author Miguel Torres Alonso
  @date Septiembre 2021

**/

class Image{

    /**
         @page page_repImagen Representación del TDA Imagen

         @section sec_Image_A Título A


         Contenido de la sección A.

         @section sec_Image_B Título  B

         Contenido de la sección B.

         Referencia a la \ref sec_Image_A
       **/
private :

    /**
      @brief Puntero a la imagen almacenada

      img apunta a un array-2D dinámico de bytes que contiene la imagen en sí. Almacena tantos bytes como pixeles tenga la imagen.

    **/
    byte **img;

    /**
      @brief Número de filas de la imagen.
    **/
    int rows;


    /**
      @brief Número de columnas de la imagen.
    **/
    int cols;


    /**
      @brief Initialize una imagen.
      @param nrows Número de filas que tendrá la imagen. Por defecto, 0
      @param ncols Número de colwnnas que tendrá la imagen. Por defecto, 0
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre filas >= O y columnas >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
    void Initialize (int nrows= 0, int ncols= 0, byte *buffer= 0);

    /**
      @brief Lee una imagen PGM desde un archivo.
      @param file_path Ruta del archivo a leer
      @return LoadResult
    **/
    LoadResult LoadFromPGM(const char * file_path);

    /**
      @brief Copy una imagen .
      @param orig Referencia a la imagen original que vamos a copiar
      @pre Asume que no hay memoria reservada o se ha llamado antes a Destroy()
      @pre Asume this != &orig
    **/
    void Copy(const Image &orig);

    /**
      @brief Reserva o copia en memoria una imagen.
      @param nrows Número de filas que tendrá la imagen.
      @param ncols Número de colwnnas que tendrá la imagen.
      @param buffer Puntero a un buffer de datos con los que rellenar los píxeles de la imagen. Por defecto, 0.
      @pre nrows >= O y ncols >= O
      @post Reserva memoria para almacenar la imagen y la prepara para usarse.
    **/
    void Allocate(int nrows, int ncols, byte * buffer = 0);

    /**
      * @brief Destroy una imagen
      *
      * Libera la memoria reservada en la que se almacenaba la imagen que llama a la función.
      * Si la imagen estaba vacía no hace nada .
      */
    void Destroy();

public :

    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase Imagen con O filas y O colunmas.
      * @return Imagen, el objeto imagen creado.
      */
    Image();

    /**
      * @brief Constructor con parámetros.
      * @param nrows Número de filas de la imagen.
      * @param ncols Número de columnas de la imagen.
      * @param value defecto Valor con el que inicializar los píxeles de la imagen . Por defecto O.
      * @pre n fils > O Y n_cols > O
      * @post La imagen creada es de n_fils y n_cols columnas. Estará inicializada al valor por defecto.
      * @return Imagen, el objeto imagen creado.
      */
    Image(int nrows, int ncols, byte value=0);

    /**
      * @brief Constructor de copias.
      * @param orig Referencia a la imagen original que se quiere copiar.
      * @return Imagen, el objeto imagen creado.
      */
    Image (const Image & orig);

    /**
      * @brief Oper ador de tipo destructor.
      * @return void
      * @post El objeto Imagen destruido no puede usarse salvo que se haga sobre él una operacion Imagen().
      */
    ~Image() ;

    /**
      * @brief Operador de asignación .
      * @param orig Referencia a la imagen original que desea copiarse.
      * @return Una referencia al objeto imagen modificado.
      * @post Destroy cualquier información que contuviera previamente la imagen que llama al operador de asignación.
      */
    Image & operator= (const Image & orig);

    /**
      * @brief Funcion para conocer si una imagen está vacía.
      * @return Si la imagene está vacía
      * @post la imagen no se modifica.
      */
    bool Empty() const;

    /**
      * @brief Filas de la imagen .
      * @return El número de filas de la i magen.
      * @post la imagen no se modifica.
      */
    int get_rows() const;

    /**
      * @brief Columnas de la imagen.
      * @return El número de columnas de la imagen.
      * @post la imagen no se modifica.
      */
    int get_cols() const;

    /**
      * @brief Devuelve el número de píxeles de la imagen.
      * @return número de píxeles de la imagen.
      * @post la imagen no se modifica.
      */
    int size() const;

    /**
      * @brief Asigna el valor valor al píxel (@p i, @p j) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a escribir .
      * @param j Columna de la imagen en la que se encuentra el píxel a escribir.
      * @param value Valor que se escribirá en el píxel (@p i, @p j) .
      * @pre O <= @p i < get_rows()
      * @pre O <= @p j < get_cols()
      * @pre O <= @p value <= 255
      * @post El píxel (@p i, @p j) de la imagen se modificará y contendrá valor @p value.
      * Los demás píxeles permanecerán iguales.
      */
    void set_pixel (int i, int j, byte value);

    /**
      * @brief Consulta el valor del píxel (fil, col) de la imagen.
      * @param i Fila de la imagen en la que se encuentra el píxel a consultar.
      * @param j Columna de la imagen en la que se encuentra el píxel a consultar.
      * @pre O <= fil < I.Num_ Filas() II O <= col < I.Num Columnas()
      * @return el valor del píxel contenido en (fil,col)
      * @post La imagen no se modifica.
      */
    byte get_pixel (int i, int j) const;

    /**
      * @brief Consulta el valor del píxel k de la imagen desenrrollada.
      * @param k Índice del píxel
      * @pre 0 <= k < filas*columnas
      * @return el valor del píxel contenido en (k/filas,k%filas)
      * @post La imagen no se modifica.
      */
    byte get_pixel (int k) const;

    /**
      * @brief Asigna el valor valor al píxel k de la imagen desenrollada.
      * @param k Índice del píxel a escribir .
      * @param value Valor que se escribirá en el píxel k.
      * @pre 0 <= k < filas*columnas && O <= valor <= 255
      * @post El píxel k se modificará con el valor de value.
      */
    void set_pixel (int k, byte value);

    /**
      * @brief Almacena imágenes en disco.
      * @param file_path Ruta donde se almacenará la imagen.
      * @pre file path debe ser una ruta válida donde almacenar el fichero de salida.
      * @return Devuelve true si la imagen se almacenó con éxito y false en caso contrario.
      * @post La imagen no se modifica.
      */
    bool Save (const char * file_path) const;

    /**
      * @brief Carga en memoria una imagen de disco .
      * @param file_path Ruta donde se encuentra el archivo desde el que cargar la imagen.
      * @pre @p file_path debe ser una ruta válida que contenga un fichero . pgm
      * @return Devuelve @b true si la imagen se carga con éxito y @b false en caso contrario.
      * @post La imagen previamente almacenada en el objeto que llama a la función se destruye.
      */
    bool Load (const char * file_path);

    /**
     * @brief Invierte los píxeles de una imagen
     * @post La imagen queda invertida
     */
    void Invert();

    // Modifica el contraste de una Imagen .
    /**
     * @brief Modifica el contraste de una imagen.
     * @param in1 Umbral inferior de la imagen de entrada
     * @param in2 Umbral superior de la imagen de entrada
     * @param out1 Umbral inferior de la imagen de salida
     * @param out2 Umbral superior de la imagen de salida
     * @pre @p 0 <= (in1, in2, int3, int4) <= 255.
                in1 < in2,
                out1 <out2
     * @post El objeto que llama a la función es modificado
     */
    void AdjustContrast (byte in1, byte in2, byte out1, byte out2);

    // Genera un icono como reducción de una imagen.
    /**
     * @brief Genera un ícono como reducción de una imagen.
     * @param factor Factor de reducción de la imgagen original con respecto al ícono
     * @pre @p Factor > 0
     * @return La imagen iconizada
     * @post La imagen no se modifica. La imagen resultante tendrá tamaño int(filas/factor) X int(columnas/factor). Descartando los decimales de la división
     */
    Image Subsample(int factor) const;

    // Genera una subimagen.
    /**
      * @brief Genera una subimagen.
      * @param nrow Número de fila donde se va a empezar a recortar.
      * @param ncol Número de columnas donde se va a empezar a recortar.
      * @param height Número a sumar a nrow.
      * @param width Número a sumar a ncol
      * @pre @p Los valores recibidos como parámetros tienen que estar dentro de las coordenadas de la imagen y no salirse de ella.
      * @return Imagen con recorte
      * @post El objeto que llama a la función no se modifica
      */
    Image Crop(int nrow, int ncol, int height, int width) const;

    // Genera una imagen aumentada 2x.
    /**
      * @brief Realiza un aumento x2 a una zona específica de una imagen.
      * @param nrow Número de fila donde se va a empezar a recortar.
      * @param ncol Número de columnas donde se va a empezar a recortar.
      * @param height Número a sumar a nrow.
      * @param width Número a sumar a ncol
      * @pre @p Los valores dados tienen que estar dentro de las coordenadas de la imagen y no salirse de ella
      * @return La imagen ampliada si nada ha fallado
      * @post El objeto que llama a la función no se modifica
      */
    Image Zoom2X(int nrow, int ncol, int height, int width) const;

    // Metodos aux para Zoon2x
    /**
      * @brief Método auxiliar de zoom para calcular la interpolación de las columnas
      */
    void interpolarCol();

    /**
     * @brief Método auxiliar de zoom para calcular la interpolación de las filas
     */
    void interpolarFil();

    // Baraja pseudoaleatoriamente las filas de una imagen.
    /**
     * @brief Realiza un recorte específico de una imagen.
     * @pre @p Rows < 9973
     * @return La imagen barajada
     * @post El objeto que llama al método contiene ahora una nueva imagen igual que la anterior pero
                con las filas ordenadas según el siguiente algoritmo: r = (r * p) % row
     */
    void ShuffleRows();
} ;


#endif // _IMAGEN_H_

