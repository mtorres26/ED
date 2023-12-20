/**
 * @file pais.h
 * @brief Cabecera para la clase Pais
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */
#ifndef PRACTICAFINAL_PAIS_H
#define PRACTICAFINAL_PAIS_H

#include "punto.h"
#include <iostream>

using namespace std;

/**
  @brief T.D.A. Pais

  Una instancia del tipo de dato abstracto Pais nos permite representar un país con su nombre, bandera y coordenadas.

  Para poder usar el TDA Pais se debe incluir el fichero

  \#include <pais.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

class Pais {

private:
    Punto p;
    string pais;
    string bandera;

public:

    // ///////////// //
    // CONSTRUCTORES //
    // ///////////// //
    /**
     * @brief Constructor primitivo sin parámetros
     */
    Pais();

    /**
     * @brief Constructor con parámetros
     * @param _p Punto contenido en el país
     * @param _pais Pais
     * @param _bandera Bandera
     */
    Pais(Punto _p, string _pais, string _bandera);

    // ///////////////// //
    // GETTERS Y SETTERS //
    // ///////////////// //

    /**
     * @brief Obtener el punto del pais
     * @return Punto
     */
    Punto GetPunto()const;

    /**
     * @brief Obtener el nombre del pais
     * @return Nombre del pais
     */
    string GetPais()const;

    /**
     * @brief Obtener la bandera del pais
     * @return Bandera
     */
    string GetBandera()const;

    /**
     * @brief Establecemos el Punto del país
     * @param _punto Punto del país
     */
    void setPunto(const Punto &_punto);

    /**
     * @brief Establecemos el nombre del país
     * @param _pais Nombre del país
     */
    void setPais(string _pais);

    /**
     * @brief Establecemos la bandera del país
     * @param _bandera Bandera del país
     */
    void setBandera(string _bandera);

    // //////////////////////// //
    // SOBRECARGA DE OPERADORES //
    // //////////////////////// //

    /**
     * @brief Sobrecarga del operador '='
     * @param P Pais que definirá el contenido del actual
     * @return Pais actual modificado
     */
    Pais & operator=(const Pais &P);

    /**
     * @brief Sobrecarga del operador menor '<'
     * @param P Pais con el que comparamos nuestro país
     * @return TRUE si el pais actual es menor que P (en orden alfabético), FALSE en caso contrario
     */
    bool operator<(const Pais &P)const;

    /**
     * @brief Sobrecarga del operador de igualdad '=='
     * @param P Pais con el que comparamos el país actual
     * @return TRUE si los paises son iguales, FALSE en caso contrario
     */
    bool operator==(const Pais &P)const;

    /**
     * @brief Sobcrecarga del operador de igualdad '=='
     * @param P Punto del país con el que comparamos el Punto del pais actual
     * @return TRUE si los puntos son iguales, FALSE en caso contrario
     */
    bool operator==(const Punto &P)const;

    // OPERADORES DE E/S

    /**
     * @brief Sobrecarga del operador de entrada '>>'
     * @param is Flujo de entrada de datos
     * @param P País que definimos
     * @return Flujo de datos de entrada
     */
    friend istream & operator>>(istream & is, Pais & P){
        double lat,lng;

        is>>lat>>lng>>P.pais>>P.bandera;

        P.p=Punto(lat,lng);
        return is;
    }

    /**
     * @brief Sobcrecarga del operador de salida
     * @param os Flujo de salida de datos
     * @param p País que mostramos por pantalla
     * @return Flujo de datos de salida
     */
    friend ostream & operator<<(ostream & os, const Pais &P){
        os<<P.p<<" "<<P.pais<<" "<<P.bandera<<endl;
        return os;
    }

};




#endif //PRACTICAFINAL_PAIS_H