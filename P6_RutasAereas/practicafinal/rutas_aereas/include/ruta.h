/**
 * @file ruta.h
 * @brief Cabecera para la clase Ruta
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include<set>
#include<string>
#include "punto.h"

using namespace std;

/**
  @brief T.D.A. Ruta

  Una instancia del tipo de dato abstracto Ruta nos permite representar ciertas localizaciones en un sistema de coordenadas.

  Para poder usar el TDA Ruta se debe incluir el fichero

  \#include <ruta.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

class Ruta {
private:
    string codigo;
    set<Punto> puntos;

public:


};