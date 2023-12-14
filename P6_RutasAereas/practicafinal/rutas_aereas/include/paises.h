/**
 * @file paises.h
 * @brief Cabecera para la clase Paises
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

using namespace std;

/**
  @brief T.D.A. Paises

  Una instancia del tipo de dato abstracto Paises nos permite representar un conjunto de instancias del TDA Pais.

  Para poder usar el TDA Paises se debe incluir el fichero

  \#include <paises.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

#include "pais.h"
#include <set>

using namespace std;

class Paises {
private:
    set <Pais> datos;

public:
    Paises();

    void Insertar(const Pais &P);

    void Borrar(const Pais &P);

    class iterator;
    class const_iterator;

};
