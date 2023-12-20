/**
 * @file almacen_rutas.cpp
 * @brief Fichero con las implementaciones para la clase AlmacenRutas
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include <iostream>
#include <map>
#include "almacen_rutas.h"

using namespace std;

// ///////////// //
// CONSTRUCTORES //
// ///////////// //

AlmacenRutas::AlmacenRutas(){
}

AlmacenRutas::AlmacenRutas(map<string,Ruta> a){
    this->almacen=a;
}

// ///////////////// //
// GETTERS Y SETTERS //
// ///////////////// //

Ruta AlmacenRutas::getRuta(string c){

    map<string,Ruta>::iterator it;

    it=almacen.find(c);

    return (*it).second;
}

map<string,Ruta> AlmacenRutas::getAlmacen(){
    return this->almacen;
}

void AlmacenRutas::setRuta(string c){
    // ¿ Qué podemos hacer en este método?
}

void AlmacenRutas::setAlmacen(const map<string,Ruta> &A){
    this->almacen=A;
}

// ///////////// //
// OTROS MÉTODOS //
// ///////////// //

void AlmacenRutas::insertarRuta(const Ruta &r){
    //map<string,Ruta>::iterator it=this->almacen.end();
    iterator it=almacen.end();
    pair<string,Ruta> ruta_aux(r.getCodigoRuta(),r);
    this->almacen.insert(ruta_aux);
}

void AlmacenRutas::eliminarRuta(string codigo){
    // Buscaremos la ruta:
    iterator it=almacen.find(codigo);

    // En caso de que exista, la ruta con código==codigo será eliminada.
    if(it.p!=this->almacen.end()){
        this->almacen.erase(it.p);
    }
}

// //////////////////////// //
// SOBRECARGA DE OPERADORES //
// //////////////////////// //

AlmacenRutas & AlmacenRutas::operator=(const AlmacenRutas &A){
    if(this!=&A){
        this->setAlmacen(A.almacen);
    }

    return *this;
}

bool AlmacenRutas::operator==(const AlmacenRutas &A)const{

    bool iguales=true;

    if(this->almacen.size() == A.almacen.size()){

        map<string,Ruta>::const_iterator it;
        map<string,Ruta>::const_iterator ot;

        ot=A.almacen.begin();


        for(it=this->almacen.begin();it!=this->almacen.end() && iguales;it++,ot++) {
            if(*it!=*ot){
                iguales=false;
            }
        }
    }else{
        iguales=false;
    }

    return iguales;
}