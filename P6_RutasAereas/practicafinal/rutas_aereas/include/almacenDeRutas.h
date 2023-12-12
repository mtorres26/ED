/**
 * @file almacenDeRutas.h
 * @brief Cabecera para la clase AlmacenDeRutas
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include<set>
#include "ruta.h"

using namespace std;

/**
  @brief T.D.A. Almacen de Rutas

  Una instancia del tipo de dato abstracto Almacen de Rutas nos permite representar ciertas localizaciones en un sistema de coordenadas.

  Para poder usar el TDA Almacen de Rutas se debe incluir el fichero

  \#include <almacenDeRutas.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

class AlmacenDeRutas {
private:
    set <Ruta> rutas;

public:

};