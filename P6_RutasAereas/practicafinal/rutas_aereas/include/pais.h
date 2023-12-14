/**
 * @file pais.h
 * @brief Cabecera para la clase Pais
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

using namespace std;

/**
  @brief T.D.A. Pais

  Una instancia del tipo de dato abstracto Pais nos permite representar un país con su nombre, bandera y coordenadas.

  Para poder usar el TDA Pais se debe incluir el fichero

  \#include <pais.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

#include "punto.h"
#include <string>

class Pais {
private:
    Punto p;
    string pais;
    string bandera;

public:
    Pais();

    Punto GetPunto() const;

    string GetPais() const;

    string GetBandera() const;

    bool operator<(const Pais &P) const;

    bool operator==(const Pais &P) const;

    bool operator==(const Punto &P) const;

};