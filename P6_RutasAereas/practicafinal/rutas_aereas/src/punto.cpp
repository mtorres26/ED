#include "punto.h"

Punto::Punto() {
    this->latitud = 0;
    this->longitud = 0;
}

Punto::Punto(double lat, double lon) {
    this->latitud = lat;
    this->longitud = lon;
}

Punto::Punto(const Punto &orig) {
    this->latitud = orig.getLatitud();
    this->longitud = orig.getLongitud();
}

Punto &Punto::operator=(const Punto &orig) {
    if (this != &orig) {
        this->latitud = orig.getLatitud();
        this->longitud = orig.getLongitud();
    }
    return *this;
}

double Punto::getLatitud() const {
    return this->latitud;
}

double Punto::getLongitud() const {
    return this->longitud;
}

void Punto::setLongitud(double lon) {
    this->longitud = lon;
}

void Punto::setLatitud(double lat) {
    this->latitud = lat;
}

bool Punto::operator==(const Punto &otro) const {
    return (latitud == otro.getLatitud() && longitud == otro.getLongitud());
}

bool Punto::operator!=(const Punto &otro) const {
    return !(latitud == otro.getLatitud() && longitud == otro.getLongitud());
}