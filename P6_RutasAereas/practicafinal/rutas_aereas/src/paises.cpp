#include "paises.h"
#include <iostream>

using namespace std;

// ///////////// //
// CONSTRUCTORES //
// ///////////// //

Paises::Paises() {
    this->datos = {};
}

Paises::Paises(const set<Pais> &_datos) {
    this->datos = _datos;
}

/*
Paises::iterator::iterator(const set<Pais>::iterator &_p){
    this->p=_p;
}

Paises::const_iterator::const_iterator(const set<Pais>::const_iterator &_p){
    this->p=_p;
}
*/

// ////////////// //
// MÉTODOS VARIOS //
// ////////////// //


void Paises::Insertar(const Pais &P) {
    this->datos.insert(P);
}

void Paises::Borrar(const Pais &P) {
    set<Pais>::iterator it = datos.find(P);

    if (it != datos.end()) {
        cout << "Pais eliminado con metodo Borrar";
        this->datos.erase(it);
    }
}