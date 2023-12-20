/**
 * @file punto.cpp
 * @brief Fichero con las implementaciones para la clase Punto
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include "punto.h"
#include <iostream>

using namespace std;

// Implementaré los métodos que supongo que deben existir

// ///////////// //
// CONSTRUCTORES //
// ///////////// //

Punto::Punto(){
    this->latitud=0;
    this->longitud=0;
}

Punto::Punto(double _latitud, double _longitud){
    this->latitud=_latitud;
    this->longitud=_longitud;
}

Punto::Punto(const Punto &p){
    this->setLatitud(p.getLatitud());
    this->setLongitud(p.getLongitud());
}

// ///////////////// //
// GETTERS Y SETTERS //
// ///////////////// //

double Punto::getLatitud()const{
    return this->latitud;
}

double Punto::getLongitud()const{
    return this->longitud;
}

void Punto::setLatitud(double lati){
    this->latitud=lati;
}

void Punto::setLongitud(double longi){
    this->longitud=longi;
}

// //////////////////////// //
// SOBRECARGA DE OPERADORES //
// //////////////////////// //

Punto & Punto::operator=(const Punto &p){
    if(this!=&p){
        this->setLatitud(p.getLatitud());
        this->setLongitud(p.getLongitud());
    }

    return *this;
}

bool Punto::operator==(const Punto &otro)const{
    bool iguales=false;

    if(this->getLatitud()==otro.getLatitud() && this->getLongitud()==otro.getLongitud()){
        iguales=true;
    }

    return iguales;
}

bool Punto::operator!=(const Punto &otro)const{
    return this==&otro;
}