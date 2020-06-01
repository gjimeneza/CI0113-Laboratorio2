#pragma once

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
using namespace std;

#include "Nodo.h"
#include "GrafoGnr.h"

class RedNodos {
    // Representa una red de nodos.

public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de v�rtices o nodos.

    // REQ: 0 < p < 1.
    // Construye un RedNodos con N v�rtices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos v�rtices es igual a p.
    RedNodos(int N, double p);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensi�n txt) con datos separados por comas.
    // En la primera l�nea aparecer� un entero que representa la cantidad N de v�rtices.
    // Los v�rtices se identifican con n�meros de 0 a N-1.
    // Luego en cada l�nea aparecer�n los �ndices de los v�rtices asociados o
    // adyacentes, a cada v�rtice: 0, 1...N-1.
    // NOTA: todos los v�rtices son inicializados con Nodo().
    RedNodos(ifstream& archivo);

    // Construye una copia id�ntica a orig.
    RedNodos(const RedNodos& orig);

    // Destructor
    ~RedNodos();

    /* M�TODOS OBSERVADORES B�SICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de v�rtice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los v�rtices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los v�rtices 
    // adyacentes a idVrt en el RedNodos.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de v�rtices adyacentes a idVrt en el RedNodos.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el v�rtice con �ndice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    Nodo operator[](int idVrt) const;

    // EFE: retorna el total de v�rtices en el RedNodos.
    int obtTotVrt() const;

    // EFE: retorna el total de nodos susceptibles en la red.
    int obtTotVrtSusceptibles() const;

    // EFE: retorna el total de nodos infectados en la red.
    int obtTotVrtInfectados() const;

    // EFE: retorna el total de nodos resistentes en la red.
    int obtTotVrtResistentes() const;

    // EFE: retorna el total de nodos susceptibles en la red.
    int obtPrcVrtSusceptibles() const;

    // EFE: retorna el total de nodos infectados en la red.
    int obtPrcVrtInfectados() const;

    // EFE: retorna el total de nodos resistentes en la red.
    int obtPrcVrtResistentes() const;

    /* M�TODOS MODIFICADORES B�SICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el v�rtice con �ndice idVrt.
    // NOTA: retorna por referencia para que pueda ser modificado en el contexto
    // invocador.
    Nodo& operator[](int idVrt);

private:

    GrafoGnr< Nodo > red_nodos; // GrafoGnr especializado con Nodo
};

RedNodos::RedNodos(int N, double p) : red_nodos(N, p) {

}


RedNodos::RedNodos(ifstream& archivo) : red_nodos(archivo) {

}

RedNodos::RedNodos(const RedNodos& orig) : red_nodos(orig.red_nodos) {

}

RedNodos::~RedNodos() {
}

bool RedNodos::xstVrt(int idVrt) const {
    return true; // s�lo para que compile, sustituya con su c�digo
}

bool RedNodos::xstAdy(int idVrtO, int idVrtD) const {
    return true; // s�lo para que compile, sustituya con su c�digo
}

void RedNodos::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {

}

int RedNodos::obtCntVrtAdys(int idVrt) const {
    return idVrt; // s�lo para que compile, sustituya con su c�digo
}

Nodo RedNodos::operator[](int idVrt) const {
    return *(new Nodo()); // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtTotVrt() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtTotVrtSusceptibles() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtTotVrtInfectados() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtTotVrtResistentes() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtPrcVrtSusceptibles() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtPrcVrtInfectados() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

int RedNodos::obtPrcVrtResistentes() const {
    return 0; // s�lo para que compile, sustituya con su c�digo
}

Nodo& RedNodos::operator[](int idVrt) {
    return *(new Nodo()); // s�lo para que compile, sustituya con su c�digo
}


