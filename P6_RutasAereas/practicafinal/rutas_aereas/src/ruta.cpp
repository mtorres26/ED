#include <iostream>
#include "ruta.h"

using namespace std;

// ///////////// //
// CONSTRUCTORES //
// ///////////// //
Ruta::Ruta() {
    this->codigo = "";
    this->puntos = {};
}

Ruta::Ruta(string _cod, list<Punto> &_p) {
    this->codigo = _cod;
    this->puntos = _p;
}


// ///////////////// //
// GETTERS Y SETTERS //
// ///////////////// //

string Ruta::getCodigoRuta() const {
    return this->codigo;
}

list<Punto> Ruta::getPuntosRuta() const {
    return this->puntos;
}

void Ruta::setCodigoRuta(const string &cod) {
    this->codigo = cod;
}

void Ruta::setPuntosRuta(list<Punto> _puntos) {
    this->puntos = _puntos;
}

// ///////////// //
// OTROS MÉTODOS //
// ///////////// //

void Ruta::insertaPunto(const Punto &p) {
    this->puntos.push_back(p);
}

// //////////////////////// //
// SOBRECARGA DE OPERADORES //
// //////////////////////// //

Ruta &Ruta::operator=(const Ruta &P) {
    if (this != &P) {
        this->setCodigoRuta(P.codigo);
        this->setPuntosRuta(P.puntos);
    }

    return *this;
}

bool Ruta::operator<(const Ruta &P) const {
    return this->puntos.size() < P.puntos.size();
}


bool Ruta::operator==(const Ruta &P) const {
    bool iguales = true;

    // Para ser iguales, deberán tener el mismo código y el mismo número de puntos.
    if (P.codigo == this->codigo && P.puntos.size() == this->puntos.size()) {
        // Iteramos sobre cada uno de los puntos de cada conjunto de puntos
        // comprobando si contienen exactamente los mismos puntos
        list<Punto>::const_iterator it;
        list<Punto>::const_iterator ot = this->puntos.begin();
        for (it = P.puntos.begin(); it != P.puntos.end() && iguales; it++) {
            if (*it != *ot) {
                iguales = false;
            }
        }

    } else {


        iguales = false;
    }

    return iguales;
}

// Al tener ya sobrecargado el operador == será sencillo realizar este.
bool Ruta::operator!=(const Ruta &P) const {
    return this == &P;
}