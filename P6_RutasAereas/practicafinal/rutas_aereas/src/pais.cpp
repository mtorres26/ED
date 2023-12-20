/**
 * @file pais.cpp
 * @brief Fichero con las implementaciones para la clase Pais
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include "pais.h"
#include <iostream>

using namespace std;

// ///////////// //
// CONSTRUCTORES //
// ///////////// //

Pais::Pais() {
    this->p = Punto();
    this->pais = "";
    this->bandera = " ";
}

Pais::Pais(Punto _p, string _pais, string _bandera){
    this->p=_p;
    this->pais=_pais;
    this->bandera=_bandera;
}

// ///////////////// //
// GETTERS Y SETTERS //
// ///////////////// //

Punto Pais::GetPunto()const{
    return this->p;
}

string Pais::GetPais()const{
    return this->pais;
}

string Pais::GetBandera()const{
    return this->bandera;
}

void Pais::setPunto(const Punto &_punto){
    this->p=_punto;
}

void Pais::setPais(string _pais){
    this->pais=_pais;
}

void Pais::setBandera(string _bandera){
    this->bandera=_bandera;
}

// //////////////////////// //
// SOBRECARGA DE OPERADORES //
// //////////////////////// //

Pais & Pais::operator=(const Pais &P){
    if(this!= &P){
        this->p=P.GetPunto();
        this->pais=P.GetPais();
        this->bandera=P.GetBandera();
    }

    return *this;
}

bool Pais::operator<(const Pais &P)const{
    bool menor=false;

    // Suponemos que se comprobará si es menor en cuanto a orden alfabético
    if(this->pais< P.GetPais()){
        menor = true;
    }

    return menor;
}

bool Pais::operator==(const Pais &P)const{
    bool mismoPais=false;

    if(this->pais==P.pais && this->bandera==P.bandera){
        mismoPais=true;
    }

    return mismoPais;
}

bool Pais::operator==(const Punto &P)const{
    bool mismoPunto=false;

    if(this->p==P){
        mismoPunto=true;
    }

    return mismoPunto;
}