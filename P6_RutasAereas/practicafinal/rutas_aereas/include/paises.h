#ifndef PRACTICAFINAL_PAISES_H
#define PRACTICAFINAL_PAISES_H

/**
 * @file paises.h
 * @brief Cabecera para la clase Paises
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

using namespace std;

/**
  @brief T.D.A. Paises

  Una instancia del tipo de dato abstracto Paises nos permite representar un conjunto de instancias del TDA Pais.

  Para poder usar el TDA Paises se debe incluir el fichero

  \#include "paises.h"

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Noviembre 2023

**/

#include "pais.h"
#include <set>
#include <iostream>

using namespace std;

class Paises {
private:
    set<Pais> datos;

public:
    /**
     * @brief Constructor primitivo. Crea un conjunto de Paises vacío.
     */
    Paises();

    /**
     * @brief Constructor a partir de un set de paises dado.
     * @param datos Conjunto de paises a partir del cual creamos nuestro objeto.
     */
    Paises(const set<Pais> &datos);

    /**
     * @brief Añade un pais 'P' a nuestro set de Pais (datos)
     * @param P Pais a insertar
     */
    void Insertar(const Pais &P);

    /**
     * @brief Elimina el Pais 'P' de nuestro set de Pais (datos)
     * @param P Pais a eliminar
     */
    void Borrar(const Pais &P);


    class iterator {
    private:
        set<Pais>::iterator p;
    public:

        // CONSTRUCTORES

        /**
         * @brief Constructor primitivo - Crea un iterador nulo
         */
        iterator() {
        }

        /**
         * @brief Constructor de copia
         * @param i Iterator pasado que copiaremos
         */
        iterator(const iterator &i) {
            p = i.p;
        }

        /**
         * @brief Constructor de iterator a partir de un set<Pais>
         * @param p set<Pais> que usamos para crear nuestro iterator
         */
        iterator(const set<Pais>::iterator &i) {
            p = i;
        }

        // OPERADORES

        /**
         * @brief Devuelve el elemento al que apunta el iterador
         * @pre El iterador no se encuentra al final del recorrido
         * @pre El iterador es distinto de end()
         * @return Elemento de 'p' apuntado por el iterador
         */
        const Pais &operator*() const {
            return *p;
        }

        /**
         * brief Operador de incremento
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el siguiente elemento, y establece el iterador a esa posición.
         */
        iterator &operator++() {
            ++p;
            return *this;
        }

        /**
         * @brief Operador de decremento
         * @pre EL iterador no está al principio del recorrido (es distinto de begin())
         * @return Devuelve el elemento anterior, y establece el iterador a esa posición.
         */
        iterator &operator--() {
            --p;
            return *this;
        }

        /**
         * @brief Operador de igualdad
         * @param ot Un iterator
         * @return TRUE Si el iterador pasado como parámetro es igual que 'p' y FALSE en caso contrario
         */
        bool operator==(const iterator &ot) {
            bool iguales = false;

            if (ot.p == p) {
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
            return ot.p != p;
        }

        /**
         * @brief Sobrecarga del operador '='
         * @param it Iterador que que "sustituye" al actual
         * @return Iterador actual modificado
         */
        iterator &operator=(const iterator &ot) {
            if (this->p != ot.p) {
                this->p = ot.p;
            }

            return *this;
        }

        /**
         * @brief Definimos Paises como clase amiga
         */
        friend class Paises;

        /**
         * @brief Definimos const_iterator como clase amiga
         */
        friend class const_iterator;
    };


    class const_iterator {
    private:
        set<Pais>::const_iterator p;
    public:

        /**
         * @brief Constructor primitivo - Crea un iterador nulo
         */
        const_iterator() {
        }

        /**
         * @brief Constructor de copia
         * @param i Iterator pasado que copiaremos
         */
        const_iterator(const iterator &i) {
            p = i.p;
        }

        /**
         * @brief Constructor con parámetros
         * @param i set<Pais>::const_iterator a partir del cual creamos el nuestro
         */
        const_iterator(const set<Pais>::const_iterator &i) {
            p = i;
        }

        /**
         * @brief Devuelve el elemento al que apunta el iterador
         * @pre El iterador no se encuentra al final del recorrido
         * @pre El iterador es distinto de end()
         * @return Elemento de 'p' apuntado por el iterador
         */
        const Pais &operator*() const {
            return *p;
        }

        /**
         * brief Operador de incremento
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el siguiente elemento, y establece el iterador a esa posición.
         */
        const_iterator &operator++() {
            p++;
            return *this;
        }

        /**
         * @brief Operador de decremento
         * @pre EL iterador no está al principio del recorrido (es distinto de begin())
         * @return Devuelve el elemento anterior, y establece el iterador a esa posición.
         */
        const_iterator &operator--() {
            p--;
            return *this;
        }

        /**
         * @brief Operador de igualdad
         * @param ot Un iteraror
         * @return TRUE Si el iterador pasado como parámetro es igual que 'p' y FALSE en caso contrario
         */
        bool operator==(const const_iterator &ot) const {
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
        bool operator!=(const const_iterator &ot) const {
            // Nos podemos apoyar en el opeardor != que ya hemos creado en Punto.
            return p != ot.p;
        }

        /**
         * @brief Sobrecarga del operador '='
         * @param it const_iterator que que "sustituye" al actual
         * @return const_iterator actual modificado
         */
        const_iterator &operator=(const const_iterator &ot) {
            // Lo modificaremos sólo si es distinto al actual
            if (this->p != ot.p) {
                this->p = ot.p;
            }

            return *this;
        }

        /**
         * @brief Definimos 'Paises' como clase amiga
         */
        friend class Paises;
    };

    /**
     * @brief Establecemos la funcionalidad begin() del iterator
     * @return Iterador que apunta al primer Pais del conjunto de paises
     */
    iterator begin() {
        iterator it;
        it.p = this->datos.begin();
        return it;
    }

    /**
     * @brief Establecemos la funcionalidad begin() del const_iterator
     * @return Iterador que apunta al primer Pais del conjunto de paises
     */
    const_iterator begin() const {
        const_iterator it;
        it.p = this->datos.begin();
        return it;
    }

    // END //

    /**
     * @brief Establecemos la funcionalidad end() del iterator
     * @return Iterador que apunta al último Pais del conjunto de paises.
     */
    iterator end() {
        iterator it;
        it.p = this->datos.end();
        return it;
    }

    /**
     * @brief Establecemos la funcionalidad end() del const_iterator
     * @return Iterador que apunta al último Pais del conjunto de paises.
     */
    const_iterator end() const {
        const_iterator it;
        it.p = this->datos.end();
        return it;
    }

    // FIND //

    /**
     * @brief Devuelve el iterador que apunta al Pais pasado como parámetro
     * @param p Pais que buscamos dentro del conjunto de paises
     * @return Iterador que apunta al Pais pasado como parámetro o end() si no existe.
     */
    iterator find(const Pais &p) {
        iterator it;
        set<Pais>::iterator i;

        // Simplemente se itera sobre 'i' hasta que encontremos el Pais 'P'
        for (i = this->datos.begin(); i != this->datos.end() && !((*i) == p); ++i);

        it.p = i;

        // Es decir, se devuelve end() si no está, y si sí está, se devuelve el iterador correspondiente
        return it;
    }

    /**
     * @brief Devuelve el iterador que apunta al Punto pasado como parámetro
     * @param p Punto que buscamos dentro del conjunto de paises
     * @return Iterador que apunta al Pais pasado como parámetro o end() si no existe.
     */
    iterator find(const Punto &p) {
        iterator it;

        set<Pais>::iterator ot;

        // Teniendo el operador == de Punto sobrecargado, podremos usarlo para esta búsqueda.
        for (ot = datos.begin(); ot != datos.end() && ((ot->GetPunto()) == p); ot++);

        // Se establece el valor de nuestro iterador en función de si ha encontrado el Punto entre los Paises
        it.p = ot;

        // Es decir, se devuelve end() si no está, y si sí está, se devuelve el iterador correspondiente
        return it;
    }

    friend istream &operator>>(istream &is, Paises &R) {
        Paises rlocal;
        //leemos el comentario
        if (is.peek() == '#') {
            string a;
            getline(is, a);
        }

        Pais P;
        while (is >> P) {
            rlocal.Insertar(P);

        }
        R = rlocal;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Paises &R) {
        Paises::const_iterator it;
        for (it = R.begin(); it != R.end(); ++it) {
            os << *it << "\t";
        }
        return os;
    }

};
#endif