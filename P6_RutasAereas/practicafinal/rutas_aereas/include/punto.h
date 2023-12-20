#ifndef __PUNTO__
#define __PUNTO__

/**
 * @file punto.h
 * @brief Cabecera para la clase Punto
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include <iostream>

using namespace std;

/**
  @brief T.D.A. Punto

  Una instancia del tipo de dato abstracto Punto nos permite representar ciertas localizaciones en un sistema de coordenadas.

  Para poder usar el TDA Punto se debe incluir el fichero

  \#include <punto.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

class Punto {
private:
    double latitud, longitud;
    // Hemos decidido no utilizar el atributo de cadena de texto

public:

    // Definiré los métodos que supongo que deben existir:

    // ///////////// //
    // CONSTRUCTORES //
    // ///////////// //
    /**
     * @brief Constructor primitivo - Sin parámetros
     */
    Punto();

    /**
     * @brief Constructor con parámetros
     * @param _latitud Latitud que tendrá nuestro nuevo Punto
     * @param _longitud Longitud que tendrá nuestro nuevo Punto
     */
    Punto(double _latitud, double _longitud);

    /**
     * @brief Constructor de copia
     * @param p Punto a partir del cual crearemos el actual
     */
    Punto(const Punto &p);

    // ///////////////// //
    // GETTERS Y SETTERS //
    // ///////////////// //
    /**
     * @brief Obtenemos la latitud del punto
     * @return Latitud del punto
     */
    double getLatitud()const;

    /**
     * @brief Obtenemos la longitud del punto
     * @return LOngitud del punto
     */
    double getLongitud()const;

    /**
     * @brief Establecemos la latitud del punto
     * @param lati Nuevo latitud
     */
    void setLatitud(double lati);

    /**
     * @brief Establecemos la longitud del punto
     * @param longi Nueva longitud
     */
    void setLongitud(double longi);

    // //////////////////////// //
    // SOBRECARGA DE OPERADORES //
    // //////////////////////// //

    /**
     * @brief Sobrecarga del opeardor '='
     * @param p Punto que sustituirá el contenido del actual
     * @return Punto actual modificado
     */
    Punto & operator=(const Punto &p);

    /**
     * @brief Sobrecarga del operador '=='
     * @param otro Punto con el que comparamos el punto actual
     * @return TRUE Si son iguales, FALSE en caso contrario
     */
    bool operator==(const Punto &otro)const;

    /**
     * @brief Sobrecarga del operador '!='
     * @param otro Punto con el que comparamos el punto actual
     * @return TRUE Si son distintos, FALSE en caso contrario
     */
    bool operator!=(const Punto &otro)const;

    /**
     * @brief Sobcrecarga del operador de salida
     * @param os Flujo de salida de datos
     * @param p Punto que mostramos por pantalla
     * @return Flujo de datos de salida
     */
    friend ostream & operator<<(ostream &os, const Punto &p){
        os << "(" << p.getLatitud() << "," << p.getLongitud() << ")";
        return os;
    }

    /**
     * @brief Sobrecarga del operador de entrada >>
     * @param is Flujo de entrada de datos
     * @param p Punto que definimos
     * @return Flujo de datos de entrada
     */
    friend istream & operator>>(istream &is, Punto &p) {

        // Leemos el paréntesis izquierdo
        char p_izq;
        is >> p_izq;

        if (p_izq != '(') {
            cout << "Error con el formato " << endl;
        }

        // Leemos la latitud
        double lat;
        is >> lat;
        p.setLatitud(lat);

        // Leemos la coma
        char coma;
        is >> coma;

        if (coma != ',') {
            cout << "Error con el formato" << endl;
        }

        // Leemos la longitud
        double log;
        is >> log;
        p.setLongitud(log);

        // Leemos el parentesis derecho
        char p_dcha;
        is >> p_dcha;

        if (p_dcha != ')') {
            cout << "Error con el formato " << endl;
        }


        return is;
    }

};

#endif