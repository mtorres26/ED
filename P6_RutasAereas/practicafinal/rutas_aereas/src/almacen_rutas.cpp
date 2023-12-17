#include <iostream>
#include <map>
#include "almacen_rutas.h"

using namespace std;

// ///////////// //
// CONSTRUCTORES //
// ///////////// //

AlmacenRutas::AlmacenRutas() {
    this->almacen = {};
}

AlmacenRutas::AlmacenRutas(map<string, Ruta> a) {
    this->almacen = a;
}

// ///////////////// //
// GETTERS Y SETTERS //
// ///////////////// //

Ruta AlmacenRutas::getRuta(string c) const {

    map<string, Ruta>::const_iterator it;

    it = almacen.find(c);

    return (*it).second;
}

map<string, Ruta> AlmacenRutas::getAlmacen() const {
    return this->almacen;
}

void AlmacenRutas::setRuta(string c) {
    // ¿ Qué podemos hacer en este método?

}

void AlmacenRutas::setAlmacen(const map<string, Ruta> &A) {
    this->almacen = A;
}

// ///////////// //
// OTROS MÉTODOS //
// ///////////// //

void AlmacenRutas::insertarRuta(const Ruta &r) {
    pair<string, Ruta> ruta_aux = make_pair(r.getCodigoRuta(), r);
    this->almacen.insert(ruta_aux);
}

void AlmacenRutas::eliminarRuta(string codigo) {
    // Buscaremos la ruta:
    iterator it = almacen.find(codigo);

    // En caso de que exista, la ruta con código==codigo será eliminada.
    if (it.p != this->almacen.end()) {
        this->almacen.erase(it.p);
    }
}

// //////////////////////// //
// SOBRECARGA DE OPERADORES //
// //////////////////////// //

AlmacenRutas &AlmacenRutas::operator=(const AlmacenRutas &A) {
    if (this != &A) {
        this->setAlmacen(A.getAlmacen());
    }
    return *this;
}

bool AlmacenRutas::operator==(const AlmacenRutas &A) const {

    bool iguales = true;

    if (this->almacen.size() == A.almacen.size()) {

        map<string, Ruta>::const_iterator it;
        map<string, Ruta>::const_iterator ot;

        ot = A.almacen.begin();


        for (it = this->almacen.begin(); it != this->almacen.end() && iguales; it++, ot++) {
            if (*it != *ot) {
                iguales = false;
            }
        }
    } else {
        iguales = false;
    }

    return iguales;
}