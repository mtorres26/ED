/**
 * @file punto.h
 * @brief Cabecera para la clase Punto
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

using namespace std;

/**
  @brief T.D.A. Punto

  Una instancia del tipo de dato abstracto Punto nos permite representar ciertas localizaciones en un sistema de coordenadas.

  Para poder usar el TDA Punto se debe incluir el fichero

  \#include <punto.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

class Punto {
private:
    double latitud, longitud;

public:
    Punto();

    Punto(double lat, double lon);

    Punto &operator=(const Punto &orig);

    double getLatitud() const;

    double getLongitud() const;
};