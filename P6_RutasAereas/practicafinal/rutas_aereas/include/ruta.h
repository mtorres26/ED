#ifndef PRACTICAFINAL_RUTA_H
#define PRACTICAFINAL_RUTA_H
/**
 * @file ruta.h
 * @brief Cabecera para la clase Ruta
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#include<list>
#include<string>
#include "punto.h"

using namespace std;

/**
  @brief T.D.A. Ruta

  Una instancia del tipo de dato abstracto Ruta nos permite representar ciertas localizaciones en un sistema de coordenadas.

  Para poder usar el TDA Ruta se debe incluir el fichero

  \#include "ruta.h"

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

class Ruta {
private:
    string codigo;
    list <Punto> puntos;

public:
    /**
     * @brief Crea ruta vacía
     */
    Ruta();

    /**
     * @brief Crea una ruta nueva
     * @param _cod Código de la nueva ruta.
     * @param _p Lista de puntos de la nueva ruta
     */
    Ruta(string _cod, list <Punto> &_p);

    /**
     * @brief Devuelve el código de la ruta
     * @return El código de la ruta
     */
    string getCodigoRuta() const;

    /**
    * @brief Devuelve la lista de puntos de la ruta
    * @return La lista de puntos de la ruta.
    */
    list <Punto> getPuntosRuta() const;

    /**
     * @brief Añade un nuevo punto a la ruta
     * @param pt Nuevo punto a insertar
     */
    void insertaPunto(const Punto &pt);

    /**
     * @brief Establece un nuevo código para la ruta
     * @param cod Nuevo código
     */
    void setCodigoRuta(const string &cod);

    /**
     * @brief Establece una nueva lista de puntos para la ruta
     * @param pts Nueva lista de puntos
     */
    void setPuntosRuta(list <Punto> pts);

    /**
     * @brief Sobrecarga del operador '='
     * @param otro Contiene la nueva ruta
     * @return Ruta modificada
     */
    Ruta &operator=(const Ruta &otro);

    /**
     * @brief Sobrecarga del operador '<' (en función del número de puntos)
     * @param P Ruta con la que queremos comparar la actual
     * @return TRUE si la ruta actual tiene menos puntos que P, FALSE en caso contrario.
     */
    bool operator<(const Ruta &P) const;

    /**
     * @brief Sobrecarga del operador '=='
     * @param r Ruta con la que comparamos la actual
     * @return TRUE si la ruta P es igual que la actual, FALSE en caso contrario.
     */
    bool operator==(const Ruta &r) const;

    /**
    * @brief Sobrecarga del operador '!='
    * @param P Ruta con la que comparamos la actual
    * @return FALSE si la ruta P es igual que la actual, TRUE en caso contrario.
    */
    bool operator!=(const Ruta &P) const;

    /**
    * @brief Sobrecarga del operador de entrada '>>'
    *
    * Formato de una ruta:
    * Codigo_Ruta Número_Puntos_De_La_Ruta <Cada una de los puntos de la ruta separados por un espacio en blanco>
    * Ejemplo:
    * R1 2 (34.52041,69.20082) (52.50786,13.42614)
    *
    * @param is Flujo de entrada
    * @param P Ruta en la que escribimos
    * @return Flujo de entrada
    */
    friend istream &operator>>(istream &is, Ruta &P) {
        // Declaramos cada uno de los elementos que nos ayudarán a desarrollar el operador:
        string codigo_ruta;
        int num_puntos_de_la_ruta;

        is >> codigo_ruta >> num_puntos_de_la_ruta;

        Punto punto_ruta;
        Ruta aux;

        aux.setCodigoRuta(codigo_ruta);

        // Añadimos cada punto a nuestra ruta:
        for (int i = 0; i < num_puntos_de_la_ruta; i++) {
            // Nos apoyamos en el operador >> ya sobrecargado en Punto.h
            is >> punto_ruta;
            aux.puntos.push_back(punto_ruta);
        }
        P = aux;
        return is;
    }

    /**
    * @brief Sobrecarga del operador de salida '<<'
    *
    * Formato de una ruta:
    * Codigo_Ruta Número_Puntos_De_La_Ruta <Cada una de los puntos de la ruta separados por un espacio en blanco>
    * Ejemplo:
    * R1 2 (34.52041,69.20082) (52.50786,13.42614)
    * @param os Flujo de salida
    * @param P Ruta que se mostrará por pantalla
    * @return Flujo de salida
    */
    friend ostream &operator<<(ostream &os, const Ruta &P) {
        string c = P.codigo;
        int tam = P.puntos.size();

        os << c << " " << tam << " ";
        // Iteramos sobre la Ruta 'P' pasada, mostrando cada uno de los puntos por pantalla:

        list<Punto>::const_iterator it;

        for (it = P.puntos.begin(); it != P.puntos.end(); it++) {
            // Nos apoyamos en el ya sobrecargado operador << de Punto, para mostrar cada punto en el formato adecuado.
            os << *it << " ";
        }

        os << endl;
        return os;
    }

    class const_iterator;

    /**
     * @brief Clase Iterator para el TDA Ruta
     */
    class iterator {
    private:
        list<Punto>::iterator p;
    public:

        // Definimos / Implementamos los operadores propios del iterator:
        // Al estar apoyado sobre el TDA list, será sencillo:

        /**
         * @brief Constructor primitivo - Crea un iterator nulo
         */
        iterator() {
        }

        /**
         * @brief Constructor de copia
         * @param i iterator que copiamos
         */
        iterator(const iterator &i) {
            p = i.p;
        }

        /**
         * @brief Constructor con parámetro(s)
         * @param i Iterador de list<Punto>
         */
        iterator(const list<Punto>::iterator &i) {
            p = i;
        }

        /**
         * @brief Sobrecarga de operador * para acceder al punto de la ruta actual
         * @return EL punto de la ruta actual
         */
        const Punto &operator*() {
            // Nos apoyamos en el operador '*' ya sobrecargado de Punto
            return *p;
        }

        /**
         * brief Operador de incremento
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el siguiente Punto de la ruta, y establece el iterador a esa posición.
         */
        iterator &operator++() {
            p++;
            return *this;
        }

        /**
         * @brief Operador de decremento
         * @pre EL iterador no está al principio del recorrido (es distinto de begin())
         * @return Devuelve el Punto anterior, y establece el iterador a esa posición.
         */
        iterator &operator--() {
            p--;
            return *this;
        }

        /**
         * @brief Operador de igualdad
         * @param ot Un iterator
         * @return TRUE Si el iterador pasado como parámetro es igual que 'p' y FALSE en caso contrario
         */
        bool operator==(const iterator &ot) {
            bool iguales = false;

            if (p == ot.p) {
                iguales = true;
            }

            return iguales;
        }

        /**
         * @brief Operador de desigualdad
         * @param ot Un iterator
         * @return @return FALSE Si el iterador pasado como parámetro es igual que 'p' y TRUE en caso contrario
         */
        bool operator!=(const iterator &ot) {
            // Nos podemos apoyar en el opeardor == que ya hemos creado.
            return p == ot.p;
        }


        /**
         * @brief Definimos Ruta como clase amiga
         */
        friend class Ruta;

        /**
         * @brief Definimos const_iterator como clase amiga
         */
        friend class const_iterator;
    };

    /**
     * @brief Clase const_iterator para el TDA Ruta
     */
    class const_iterator {
    private:
        list<Punto>::const_iterator p;
    public:

        // Definimos / Implementamos los operadores propios del const_iterator:
        // Al estar apoyado sobre el TDA list, será sencillo:

        /**
         * @brief Constructor primitivo - Crea un iterator nulo
         */
        const_iterator() {
        }

        /**
         * @brief Constructor de copia
         * @param i iterator que copiamos
         */
        const_iterator(const const_iterator &i) {
            p = i.p;
        }

        /**
         * @brief Constructor con parámetro(s)
         * @param i Iterador de list<Punto>
         */
        const_iterator(const list<Punto>::const_iterator &i) {
            p = i;
        }

        /**
         * @brief Sobrecarga de operador * para acceder al punto de la ruta actual
         * @return EL punto de la ruta actual
         */
        const Punto &operator*() {
            // Nos apoyamos en el operador '*' ya sobrecargado de Punto
            return *p;
        }

        /**
         * brief Operador de incremento
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el siguiente Punto de la ruta, y establece el iterador a esa posición.
         */
        const_iterator &operator++() {
            p++;
            return *this;
        }

        /**
         * @brief Operador de decremento
         * @pre EL iterador no está al principio del recorrido (es distinto de begin())
         * @return Devuelve el Punto anterior, y establece el iterador a esa posición.
         */
        const_iterator &operator--() {
            p--;
            return *this;
        }

        /**
         * @brief Operador de igualdad
         * @param ot Un iterator
         * @return TRUE Si el iterador pasado como parámetro es igual que 'p' y FALSE en caso contrario
         */
        bool operator==(const const_iterator &ot) {
            bool iguales = false;

            if (p == ot.p) {
                iguales = true;
            }

            return iguales;
        }

        /**
         * @brief Operador de desigualdad
         * @param ot Un iterator
         * @return @return FALSE Si el iterador pasado como parámetro es igual que 'p' y TRUE en caso contrario
         */
        bool operator!=(const const_iterator &ot) {
            // Nos podemos apoyar en el operador != que ya hemos creado de Punto.
            return p != ot.p;
        }


        /**
         * @brief Definimos Ruta como clase amiga
         */
        friend class Ruta;

        /**
         * @brief Definimos iterator como clase amiga
         */
        friend class iterator;

    };

    // ////////////////////////////// //
    // FUNCIONES DE ITERADORES VARIOS //
    // ////////////////////////////// //

    // BEGIN //

    /**
     * @brief Establecemos la funcionalidad begin() del iterator
     * @return Iterador que apunta al primer Punto de la lista de puntos
     */
    iterator begin() {
        iterator it;
        it.p = this->puntos.begin();

        return it;
    }

    /**
     * @brief Establecemos la funcionalidad begin() del const_iterator
     * @return Iterador que apunta al primer Punto de la lista de puntos
     */
    const_iterator begin() const {
        const_iterator it;
        it.p = this->puntos.begin();

        return it;
    }

    // END //

    /**
     * @brief Establecemos la funcionalidad end() del iterator
     * @return Iterador que apunta al último Punto del conjunto de puntos.
     */
    iterator end() {
        iterator it;
        it.p = this->puntos.end();

        return it;
    }

    /**
     * @brief Establecemos la funcionalidad end() del const_iterator
     * @return Iterador que apunta al último Punto del conjunto de puntos.
     */
    const_iterator end() const {
        const_iterator it;
        it.p = this->puntos.end();

        return it;
    }

    // FIND //

    /**
     * @brief Devuelve el iterador que apunta al Punto pasado como parámetro
     * @param p Punto que buscamos dentro de la lista de puntos
     * @return Iterador que apunta al Punto pasado como parámetro o end() si no existe.
     */
    iterator find(const Punto &p) {
        iterator encontrado;

        list<Punto>::iterator it = this->puntos.begin();

        // Iteraremos sobre el conjunto de puntos mientras no encontremos
        while ((it != this->puntos.end()) && (p != *it)) {
            it++;
        }

        return it;
    }

};

#endif