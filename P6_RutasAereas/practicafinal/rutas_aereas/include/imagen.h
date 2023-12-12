#ifndef PRACTICAFINAL_IMAGEN_H
#define PRACTICAFINAL_IMAGEN_H

/**
 * @file imagen.h
 * @brief Cabecera para la clase Imagen
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include <cstdlib>
#include <string>

enum Tipo_Pegado {
    OPACO, BLENDING
};
using namespace std;

struct Pixel {
    unsigned char r, g, b;
    unsigned char transp; // 0 no 255 si
};

/**
  @brief T.D.A. Imagen

  Una instancia del tipo de dato abstracto Imagen nos permite almacenar imágenes de intensidades.

  El TDA Imagen proporciona además distintas herramientas para la manipulación de dichas imágenes.

  Para poder usar el TDA Imagen se debe incluir el fichero

  \#include <Imagen.h>

  @author Javier Abad
  @author Guillermo Gómez
  @date Septiembre 2021

**/

class Imagen {

private :

    /**
      @brief Puntero donde se almacena la información de la imagen

      Si la imagen está en formato PGM, almacena tantos bytes como pixeles tenga la imagen.
      Si la imagen está en formato PPM, se almacenan se almacenan 3 bytes por cada pixel de la imagen,
      donde cada byte de la tripleta de bytes representa la cantidad de color de un color primario.

    **/
    Pixel **data;

    /**
      @brief Número de filas de la imagen.
    **/
    int nf;

    /**
      @brief Número de columnas de la imagen.
    **/
    int nc;

    /**
     * @brief Borra una imagen
     */
    void Borrar();

    /**
     * @brief Copia una imagen
     * @param I
     */
    void Copiar(const Imagen &I);


public :

    /**
      * @brief Constructor por defecto .
      * @post Genera una instancia de la clase Imagen con O filas y O colunmas.
      * @return Imagen, el objeto imagen creado.
      */
    Imagen();

    /**
      * @brief Constructor con parámetros.
      * @param nf Número de filas de la imagen.
      * @param nc Número de columnas de la imagen.
      * @pre n fils > O Y n_cols > O
      * @post La imagen creada es de nf filas y nc columnas.
      * @return Imagen, el objeto imagen creado.
      */
    Imagen(int nf, int nc);

    /**
      * @brief Constructor de copias.
      * @param I Referencia a la imagen original que se quiere copiar.
      * @return Imagen, el objeto imagen creado.
      */
    Imagen(const Imagen &I);

    /**
      * @brief Operador de asignación .
      * @param orig Referencia a la imagen original que desea copiarse.
      * @return Una referencia al objeto imagen modificado.
      * @post Destroy cualquier información que contuviera previamente la imagen que llama al operador de asignación.
      */
    Imagen &operator=(const Imagen &I);

    /**
     * @brief Destructor
     */
    ~Imagen();

    /**
      * @brief Filas de la imagen .
      * @return El número de filas de la i magen.
      * @post la imagen no se modifica.
      */
    int GetFilas() const;

    /**
      * @brief Columnas de la imagen.
      * @return El número de columnas de la imagen.
      * @post la imagen no se modifica.
      */
    int GetCols() const;

    /**
      * @brief Devuelve el número de píxeles de la imagen.
      * @return número de píxeles de la imagen.
      * @post la imagen no se modifica.
      */
    int size() const;

    /**
     * @brief Acceso al pixel de la fila @param i y columna @param j
     * @param i Fila a la que pertenece el pixel al que queremos acceder
     * @param j Columna a la que pertenece el pixel al que queremos acceder
     * @return El pixel al que hemos accedido
     */
    Pixel &operator()(int i, int j);

    /**
     * @brief Acceso (sin modificacion) al pixel de la fila @param i y columna @param j
     * @param i Fila a la que pertenece el pixel al que queremos acceder
     * @param j Columna a la que pertenece el pixel al que queremos acceder
     * @return El pixel al que hemos accedido
     * @post El pixel accedido no se modifica
     */
    const Pixel &operator()(int i, int j) const;

    /**
     * @brief Crea una imagen con
     * @param nombre Nombre que tendrá la nueva imagen
     */
    void EscribirImagen(const char *nombre);

    /**
     *
     * @param nimagen
     * @param nombre_mascara
     */
    void LeerImagen(const char *nimagen, const string &nombre_mascara = "");


    void LimpiarTransp();


    void PutImagen(int posi, int posj, const Imagen &I, Tipo_Pegado tippegado = OPACO);


    Imagen ExtraeImagen(int posi, int posj, int dimi, int dimj);

};

#endif //PRACTICAFINAL_IMAGEN_H
