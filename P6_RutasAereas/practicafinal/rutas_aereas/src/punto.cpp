#include <punto.h>

Punto::Punto() {
    this->latitud = 0;
    this->longitud = 0;
}

Punto::Punto(double lat, double lon) {
    this->latitud = lat;
    this->longitud = lon;
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

