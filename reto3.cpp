/**
 * @file reto3.cpp
 * @author Miguel Torres Alonso
 * @brief Implementación del reto 3 de la asignatura Estructura de Datos
 * @version 0.1
 * @date 2023-11-20
 *
 */

#include <list>
#include <iostream>
#include <utility>

using namespace std;

template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &l);
template <typename T>
ostream &operator<<(ostream &os, const list<T> &l);

template <typename T>
ostream &operator<<(ostream &os, const pair<T, T> &l)
{
    os << '[';
    os << l.first << ", " << l.second;
    os << ']';
    return os;
}

template <typename T>
ostream &operator<<(ostream &os, const list<T> &l)
{
    os << '<';
    for (auto it = l.begin(); it != l.end(); ++it)
    {
        if (it != l.begin())
            os << ", ";
        os << *it;
    }
    os << '>';
    return os;
}

typedef pair<int, int> intervalo;

bool extraer(list<intervalo> &L1, intervalo x, list<intervalo> &L2)
{

    bool hecho = false;

    for (auto it1 = L1.begin(); it1 != L1.end(); it1++)
    {
        if (it1->first < x.first && x.second == it1->second)
        {
            it1->second = x.first - 1;
            hecho = true;
        }
        else if (it1->first < x.first && x.second < it1->second)
        {
            intervalo aux = make_pair(x.second + 1, it1->second);
            it1->second = x.first - 1;
            list<intervalo>::iterator it_aux = it1;
            it_aux++;
            L1.insert(it_aux, aux);
            hecho = true;
        }
    }
    for (auto it2 = L2.begin(); it2 != L2.end(); it2++)
    {
        auto it_aux = it2;
        if (it2->first > x.first && it2->first <= x.second && it2->second >= x.second)
        {
            it2->first = x.first;
        }
        else if (x.first < it2->first && x.second > it2->second && x.second >= it_aux->first)
        {
            intervalo aux = make_pair(x.first, it_aux->second);
            L2.erase(it_aux); // Cuidao si es end()
            L2.insert(it_aux, aux);
            L2.erase(it2);
        }
    }
    return hecho;
}

int main(int argc, char *argv[])
{
    list<intervalo> L1_1 = {{1, 7}, {10, 14}, {18, 20}, {25, 26}};
    list<intervalo> L2_1 = {{0, 1}, {14, 16}, {20, 23}};

    list<intervalo> L1_2 = {{1, 7}, {10, 22}, {25, 26}};
    list<intervalo> L2_2 = {{0, 1}, {14, 16}, {20, 23}};

    // -------------- EJEMPLO 1 ---------------------------------------
    cout << "Ejemplo 1: " << endl;
    cout << "L1_1 = " << L1_1 << endl;
    cout << "L2_1 = " << L2_1 << endl;

    intervalo x = make_pair(12, 14);
    cout << "El intervalo x es: " << x << endl;
    bool ejemplo1 = extraer(L1_1, x, L2_1);

    cout << "El ejemplo 1 es " << (ejemplo1 ? "verdadero" : "falso") << " y da como resultado: " << endl;
    cout << "L1_1 = " << L1_1 << endl;
    cout << "L2_1 = " << L2_1 << endl;

    // -------------- EJEMPLO 2 ---------------------------------------
    cout << endl
         << "Ejemplo 2: " << endl;
    cout << "L1_2 = " << L1_2 << endl;
    cout << "L2_2 = " << L2_2 << endl;

    intervalo y = make_pair(12, 20);
    cout << "El intervalo x es: " << y << endl;
    bool ejemplo2 = extraer(L1_2, x, L2_2);

    cout << "El ejemplo 2 es " << (ejemplo1 ? "verdadero" : "falso") << " y da como resultado: " << endl;
    cout << "L1_2 = " << L1_2 << endl;
    cout << "L2_2 = " << L2_2 << endl;
}