/*
 * File:   GrafoGnr.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#ifndef GRAFOGNR_H
#define GRAFOGNR_H

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

template < typename T >
class GrafoGnr {
    // Representa una red compleja gen�rica con v�rtices de tipo T.
    /* Supuestos sobre el tipo T:
    * T() est� definido.
    * T(const T&) est� definido.
    * T operator=(const T& t) est� definido.
    * friend ostream& operator<<(ostream& o, const T& t) plantilla de operador sobrecargado.
    */

public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de v�rtices o nodos.

    // REQ: 0 < p < 1.
    // Construye un GrafoGnr con N v�rtices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos v�rtices es igual a p.
    GrafoGnr(int N, double p);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensi�n txt) con datos separados por comas.
    // En la primera l�nea aparecer� un entero que representa la cantidad N de v�rtices.
    // Los v�rtices se identifican con n�meros de 0 a N-1.
    // Luego en cada l�nea aparecer�n los �ndices de los v�rtices asociados o
    // adyacentes, a cada v�rtice: 0, 1...N-1.
    // NOTA: todos los v�rtices son inicializados con T().
    GrafoGnr(ifstream& archivo);

    // Construye una copia id�ntica a orig.
    GrafoGnr(const GrafoGnr< T >& orig);

    // Destructor
    ~GrafoGnr();

    /* M�TODOS OBSERVADORES B�SICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de v�rtice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los v�rtices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los v�rtices 
    // adyacentes a idVrt en el GrafoGnr.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de v�rtices adyacentes a idVrt en el GrafoGnr.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el v�rtice con �ndice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    T operator[](int idVrt) const;

    // EFE: retorna el total de arcos o adyacencias en el GrafoGnr.
    int obtTotArc() const;

    // EFE: retorna el total de v�rtices en el GrafoGnr.
    int obtTotVrt() const;

    /* M�TODOS MODIFICADORES B�SICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el v�rtice con �ndice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    T& operator[](int idVrt);

private:

    template < typename TT >
    struct Vrt {
        TT t;
        list< int > lstAdy;

        Vrt() : t(), lstAdy() {
        }; // constructor est�ndar de Vrt

        Vrt(const TT& tt) : t(tt), lstAdy() {
        }; // constructor con dato de v�rtice

        Vrt(const Vrt< TT >& vrt) : t(vrt.t), lstAdy(vrt.lstAdy) {
        }; // constructor de copias de Vrt
    };

    vector< Vrt< T > > vectorVrts; // vector de v�rtices
};

template < typename T >
GrafoGnr< T >::GrafoGnr(int N, double p) {
}

template < typename T >
GrafoGnr< T >::GrafoGnr(ifstream& archivo) {
}

template < typename T >
GrafoGnr< T >::GrafoGnr(const GrafoGnr< T >& orig) {
}

template < typename T >
GrafoGnr< T >::~GrafoGnr() {
}

template < typename T >
bool GrafoGnr< T >::xstVrt(int idVrt) const {
    return true;
}

template < typename T >
bool GrafoGnr< T >::xstAdy(int idVrtO, int idVrtD) const {
    return true;
}

template < typename T >
void GrafoGnr< T >::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
}

template < typename T >
int GrafoGnr< T >::obtCntVrtAdys(int idVrt) const {
}

template < typename T >
T GrafoGnr< T >::operator[](int idVrt) const {
    T t;
    return t;
}

template < typename T >
int GrafoGnr< T >::obtTotArc() const {
    return 0;
}

template < typename T >
int GrafoGnr< T >::obtTotVrt() const {
    return 0;
}

template < typename T >
T& GrafoGnr< T >::operator[](int idVrt) {
    T t;
    return t;
}

#endif /* GRAFOGNR_H */
