/**
 * @file almacen_rutas.h
 * @brief Cabecera para la clase AlmacenRutas
 * @authors Alberto Ortega Vílchez, Miguel Torres Alonso
 */

#ifndef PRACTICAFINAL_ALMACENRUTAS_H
#define PRACTICAFINAL_ALMACENRUTAS_H

#include <map>
#include <string>
#include "ruta.h"

using namespace std;

/**
  @brief T.D.A. Almacen de Rutas

  Una instancia del tipo de dato abstracto Almacen de Rutas nos permite representar un conjunto de Rutas precedidas de su código.

  Para poder usar el TDA AlmacenRutas se debe incluir el fichero

  \#include <almacen_rutas.h>

  @author Alberto Ortega Vílchez
  @author Miguel Torres Alonso
  @date Diciembre 2023

**/

class AlmacenRutas{

private:
    map<string,Ruta> almacen;
    // Se representará un almacén de rutas como un map de:
    // string --> Representa el código de la ruta
    // Ruta --> Representará la Ruta (formada por puntos)
public:

    // ///////////// //
    // CONSTRUCTORES //
    // ///////////// //

    /**
     * @brief Constructor primitivo sin parámetros
     */
    AlmacenRutas();

    /**
     * @brief Constructor con parámetros
     * @param a map<string,Ruta> que usaremos para crear nuestro objeto
     */
    AlmacenRutas(map<string,Ruta> a);


    // ///////////////// //
    // GETTERS Y SETTERS //
    // ///////////////// //

    /**
     * @brief Devuelve la Ruta (código y lista de puntos) a partir de un código de ruta
     * @pre El código de ruta deberá corresponder a una ruta real contenida
     * @param c Código de ruta
     * @return Ruta buscada
     */
    Ruta getRuta(string c);

    /**
     * @brief Devuelve el almacen de rutas
     * @return Almacen de rutas
     */
    map<string,Ruta> getAlmacen();

    /**
     * @brief Se modifica una ruta determinada a partir de su código
     * @param c Código de la ruta a modificar.
     */
    void setRuta(string c);

    /**
     * @brief Modifica el Almacen de Rutas
     * @param A Almacen de Rutas
     */
    void setAlmacen(const map<string,Ruta> &A);

    // ///////////// //
    // OTROS MÉTODOS //
    // ///////////// //

    /**
     * @brief Añadimos una ruta dada a nuestro "mapa" de rutas.
     * @pre La ruta nueva no está en el Almacén
     * @param r Ruta a añadir
     */
    void insertarRuta(const Ruta &r);

    /**
     * @brief Eliminamos/extraemos una de las rutas de nuestro mapa de rutas.
     * @pre La ruta debe existir
     * @param codigo Código de la ruta eliminada
     */
    void eliminarRuta(string codigo);

    // //////////////////////// //
    // SOBRECARGA DE OPERADORES //
    // //////////////////////// //

    /**
     * @brief Sobrecarga del operador '='
     * @param A AlmacenRutas que sustituye al actual (si no es el mismo)
     * @return AlmacenRutas modificado.
     */
    AlmacenRutas & operator=(const AlmacenRutas &A);

    /**
     * @brief Sobrecarga del operador '=='
     * @param A AlmacenRutas que comprobaremos si es igual al actual
     * @return TRUE Si son iguales, FALSE en caso contrario
     */
    bool operator==(const AlmacenRutas &A)const;

    // **
     //* @brief Sobrecarga del operador '!='
     //* @param A AlmacenRutas que comprobaremos si es igual al actual
     //* @return FALSE Si son iguales, TRUE en caso contrario
     //*/
    //bool &operator!=(const AlmacenRutas &A)const;


    // OPERADORES DE E/S
    /**
     * @brief Sobrecarga del operador de salida '<<'
     *
     * Formato de un Almacén de Rutas:
     *
     * Palabra_mágica #Rutas
     * Codigo_Ruta1 Número_Puntos_De_La_Ruta1 <Cada una de los puntos de la ruta1 separados por un espacio en blanco>
     * Codigo_Ruta2 Número_Puntos_De_La_Ruta2 <Cada una de los puntos de la ruta2 separados por un espacio en blanco>
     * Ejemplo:
     * #Rutas
     * R1 2 (34.52041,69.20082) (52.50786,13.42614)
     * R2 1 (17.24640,-19.67060)
     *
     * @param os Flujo de salida
     * @param P AlmacenRutas que se mostrará por pantalla
     * @return Flujo de salida
     */
    friend ostream & operator<<(ostream & os, const AlmacenRutas &A){

        os << "#Rutas" << endl;
        map<string,Ruta>::const_iterator it;

        for(it=A.almacen.begin();it!=A.almacen.end();it++){
            // Como ya tenemos sobcrecargado el operador '<<' en Ruta.h, nos apoyaremos en este.
            // Simplemente iremos mostrando cada una de las rutas, finalizando con un salto de línea
            // El código de la ruta ya se muestra en el iterador '<<'< de Ruta.h
            os << it->second;
        }

        return os;
    }

    /**
     * @brief Sobrecarga del operador de entrada '>>'
     *
     * Formato de un Almacén de Rutas:
     *
     * Palabra_mágica #Rutas
     * Codigo_Ruta1 Número_Puntos_De_La_Ruta1 <Cada una de los puntos de la ruta1 separados por un espacio en blanco>
     * Codigo_Ruta2 Número_Puntos_De_La_Ruta2 <Cada una de los puntos de la ruta2 separados por un espacio en blanco>
     * Ejemplo:
     * #Rutas
     * R1 2 (34.52041,69.20082) (52.50786,13.42614)
     * R2 1 (17.24640,-19.67060)
     *
     * @param is Flujo de entrada
     * @param P AlmacenRutas que definiremos
     * @return Flujo de salida
     */
    friend istream & operator>>(istream & is, AlmacenRutas &A){
        AlmacenRutas aux;
        string cod_aux;

        is >> cod_aux;

        if(cod_aux=="#Rutas") {

             Ruta ruta_aux;

             // Iremos añadiendo rutas hasta llegar al final del fichero
             do{
                 is >> ruta_aux;
                 aux.insertarRuta(ruta_aux);
             }while(is.peek()!=EOF);

        }

        // De esta forma eliminaremos el último carácter añadido
        // ('#', el cuál inidica el cominenzo de otro almacén de rutas)
        // is.ignore();

        A=aux;
        return is;
    }

    // ///////////////// //
    // CLASES ITERADORAS //
    // ///////////////// //

    class const_iterator;

    /**
     * @brief Clase iterator para el TDA AlmacenRutas
     */
    class iterator{
    private:
        map<string,Ruta>::iterator p;
    public:
        // Definimos / Implementamos los operadores propios del iterator:
        // Al estar apoyado sobre el TDA map, será sencillo:
        /**
         * @brief Constructor primitivo
         */
        iterator(){}

        /**
         * @brief Constructor con parámetros
         * @param it Iterator al que estableceremos 'p'
         */
        iterator(const map<string,Ruta>::iterator &it){
            p=it;
        }

        /**
         * @brief Constructor de copia
         * @param it iterator que copiaremos en 'p'
         */
        iterator(const iterator &it){
            p=it.p;
        }

        /**
         * @brief Sobrecarga del operador '='
         * @param it Iterador que sustituye al actual
         * @return Iterador actual modificado
         */
        iterator & operator=(const iterator &it){
            p=it.p;
            return *this;
        }

        /**
         * @brief Devuelve la Ruta a la que apunta el iterador
         * @pre El iterador no se encuentra al final del recorrido
         * @pre El iterador es distinto de end()
         * @return Elemento de 'p' apuntado por el iterador
         */
        const Ruta & operator*()const{
            return (*p).second;
        }

        /**
         * @brief Sobrecarga operador '=='
         * @param it Iterador con el que comparamos el actual
         * @return TRUE Si son iguales, FALSE en caso contrario
         */
        bool operator==(const iterator &it){
            bool iguales=false;
            if(it.p==p){
                iguales=true;
            }
            return iguales;
        }

        /**
         * @brief Sobrecarga del operador '!='
         * @param it Iterador con el que comparamos el actual
         * @return TRUE Si son distintos, FALSE en caso contrario
         */
        bool operator!=(const iterator &it){
            // Nos apoyaremos en el ya sobrecargado operador '!=' de Ruta
            return it.p!=p;
        }

        /**
         * @brief Sobrecarga del operador '++'
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el iterator que apunta a la siguiente Ruta del almacén, y establece el iterador a esa posición.
         */
        iterator & operator++(){
            p++;
            return *this;
        }

        /**
         * @brief Sobrecarga del operador '--'
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el iterator que apunta a la Ruta anterior del almacén, y establece el iterador a esa posición.
         */
        iterator & operator--(){
            p--;
            return *this;
        }

        /**
         * @brief Definimos Ruta como clase amiga
         */
        friend class AlmacenRutas;

        /**
         * @brief Definimos const_iterator como clase amiga
         */
        friend class const_iterator;

    };

    /**
     * @brief Clase const_iterator para el TDA AlmacenRutas
     */
    class const_iterator{
    private:
        map<string,Ruta>::const_iterator p;
    public:
        // Definimos / Implementamos los operadores propios del const_iterator:
        // Al estar apoyado sobre el TDA map, será sencillo:

        /**
         * @brief Constructor primitivo
         */
        const_iterator(){}

        /**
         * @brief Constructor con parámetros
         * @param it const_iterator al que estableceremos 'p'
         */
        const_iterator(map<string,Ruta>::const_iterator it){
            p=it;
        }

        /**
         * @brief Constructor de copia
         * @param it const_iterator que copiaremos en 'p'
         */
        const_iterator(const const_iterator &it){
            p=it.p;
        }

        /**
         * @brief Sobrecarga del operador '='
         * @param it const_iterator que sustituye al actual
         * @return const_iterator actual modificado
         */
        const_iterator & operator=(const iterator &it){
            p=it.p;
            return *this;
        }

        /**
         * @brief Devuelve la Ruta a la que apunta el const_iterator
         * @pre El const_iterator no se encuentra al final del recorrido
         * @pre El const_iterator es distinto de end()
         * @return Elemento de 'p' apuntado por el const_iterator
         */
        const Ruta & operator*()const{
            return (*p).second;
        }

        /**
         * @brief Sobrecarga operador '=='
         * @param it Iterador con el que comparamos el actual
         * @return TRUE Si son iguales, FALSE en caso contrario
         */
        bool operator==(const const_iterator &it){
            bool iguales=false;

            if(it.p==p){
                iguales=true;
            }

            return iguales;
        }

        /**
         * @brief Sobrecarga del operador '!='
         * @param it Iterador con el que comparamos el actual
         * @return TRUE Si son distintos, FALSE en caso contrario
         */
        bool operator!=(const const_iterator &it){
            // Nos apoyaremos en el ya sobrecargado operador '=='
            return it.p!=p;
        }

        /**
         * @brief Sobrecarga del operador '++'
         * @pre El const_iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el const_iterator que apunta a la siguiente Ruta del almacén, y establece el const_iterator a esa posición.
         */
        const_iterator & operator++(){
            p++;
            return *this;
        }

        /**
         * @brief Sobrecarga del operador '--'
         * @pre EL iterador no está al final del recorrido (Es distinto de end())
         * @return Devuelve el const_iterator que apunta a la Ruta anterior del almacén, y establece el const_iterator a esa posición.
         */
        const_iterator & operator--(){
            p--;
            return *this;
        }

        /**
         * @brief Definimos AlmacenRutas como clase amiga
         */
        friend class AlmacenRutas;

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
     * @return El iterator que apunta a la primera Ruta del almacén
     */
    iterator begin(){
        iterator it;
        it.p=this->almacen.begin();

        return it;
    }

    /**
     * @brief Establecemos la funcionalidad begin() del const_iterator
     * @return El const_iterator que apunta a la primera Ruta del almacén
     */
    const_iterator begin()const{
        const_iterator it;
        it.p=this->almacen.begin();

        return it;
    }

    // END //
    /**
     * @brief Establecemos la funcionalidad end() del iterator
     * @return El iterator que apunta a la última Ruta del almacén
     */
    iterator end(){
        iterator it;
        it.p=this->almacen.end();

        return it;
    }

    /**
     * @brief Establecemos la funcionalidad begin() del const_iterator
     * @return El const_iterator que apunta a la última Ruta del almacén
     */
    const_iterator end()const{
        const_iterator it;
        it.p=this->almacen.end();

        return it;
    }

    // FIND //

    /**
     * @brief Devuelve el iterador que apunta a la Ruta ñ como parámetro
     * @param p Ruta que buscamos dentro del almacén
     * @return Iterador que apunta a la Ruta pasada como parámetro o end() si no existe.
     */
    iterator find(const Ruta &r){

        iterator it;
        bool encontrado=false;

        for(it=this->almacen.begin();it!=this->almacen.end() && !encontrado;++it){ // ¿Por qué no puedo incrementarlo con it++?

            // Si el código de la ruta pasada como parámetro coincide con el código del iterador
            // que está iterando sobre el conjunto de almacenes (es decir, con el código de alguna
            // de las rutas del almacén, significará que ha 'encontrado' la ruta.

            if(r.getCodigoRuta() == it.p->first){
                encontrado=true;
                --it;
                // Dejamos entonces de iterar (ya que no se cumple una de las 2 condiciones del for,
                // de forma que el iterador 'it' se queda apuntando a la ruta encontrada.
            }
        }

        //if(it==almacen.end() && encontrado){
        //    --it;
        //}

        // Si la ruta fue encontrada, it apuntará a esa ruta.
        // Si no fue encontrada, it apuntará a end().
        return it;
    }

};

#endif //PRACTICAFINAL_ALMACENRUTAS_H