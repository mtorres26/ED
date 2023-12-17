#ifndef PRACTICAFINAL_PAIS_H
#define PRACTICAFINAL_PAIS_H
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

  \#include "pais.h"

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

#include "punto.h"
#include <string>
#include <iostream>

class Pais {
private:
    Punto p;
    string pais;
    string bandera;

public:
    Pais();
    Pais(Punto _p, string _pais, string _bandera);

    Punto GetPunto()const;
    string GetPais()const;
    string GetBandera()const;

    void setPunto(const Punto &_punto);
    void setPais(string _pais);
    void setBandera(string _bandera);

    Pais & operator=(const Pais &P);
    bool operator<(const Pais &P)const;
    bool operator==(const Pais &P)const;
    bool operator==(const Punto &P)const;

    friend istream &operator>>(istream &is, Pais &P) {
        double lat, lng;

        is >> lat >> lng >> P.pais >> P.bandera;

        P.p = Punto(lat, lng);
        return is;
    }

    friend ostream &operator<<(ostream &os, const Pais &P) {
        os << P.p << " " << P.pais << " " << P.bandera << endl;
        return os;
    }
};
#endif