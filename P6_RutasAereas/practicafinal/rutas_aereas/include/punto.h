#ifndef PRACTICAFINAL_PUNTO_H
#define PRACTICAFINAL_PUNTO_H

/**
 * @file punto.h
 * @brief Cabecera para la clase Punto
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */
#include <string>
#include <iostream>


using namespace std;

/**
  @brief T.D.A. Punto

  Una instancia del tipo de dato abstracto Punto nos permite representar ciertas localizaciones en un sistema de coordenadas.

  Para poder usar el TDA Punto se debe incluir el fichero

  \#include "punto.h"

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

    Punto(const Punto &orig);

    double getLatitud() const;

    double getLongitud() const;

    void setLongitud(double lon);

    void setLatitud(double lat);

    Punto &operator=(const Punto &orig);

    bool operator==(const Punto &otro) const;

    bool operator!=(const Punto &otro) const;

    friend ostream &operator<<(ostream &os, const Punto &pt) {
        os << "(" << pt.latitud << "," << pt.longitud << ")";
        return os;
    }

    friend istream &operator>>(istream &is, Punto &pt) {
        string lat, lng;
        string aux;

        getline(is, aux, '(');
        getline(is, lat, ',');
        getline(is, lng, ')');

        double lat_d = stod(lat);
        double lng_d = stod(lng);
        pt.setLatitud(lat_d);
        pt.setLongitud(lng_d);
        return is;
    }

};
#endif