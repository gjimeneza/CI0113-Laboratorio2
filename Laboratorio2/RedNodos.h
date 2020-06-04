#pragma once

#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <algorithm>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <assert.h>
using namespace std;

#include "Nodo.h"
#include "GrafoGnr.h"

class RedNodos {
    // Representa una red de nodos.

public:
    /* CONSTRUCTORES */

    // DADOS:
    // N la cantidad de vértices o nodos.

    // REQ: 0 < p < 1.
    // Construye un RedNodos con N vértices en el que el conjunto de
    // adyacencias se determina aleatoriamente utilizando p. Esto
    // implica que la probabilidad de que un arco exista entre 
    // cualesquiera dos vértices es igual a p.
    RedNodos(int N, double p);

    // Construye una red con base en los datos en el archivo.
    // El archivo debe ser de texto (extensión txt) con datos separados por comas.
    // En la primera línea aparecerá un entero que representa la cantidad N de vértices.
    // Los vértices se identifican con números de 0 a N-1.
    // Luego en cada línea aparecerán los índices de los vértices asociados o
    // adyacentes, a cada vértice: 0, 1...N-1.
    // NOTA: todos los vértices son inicializados con Nodo().
    RedNodos(ifstream& archivo);

    // Construye una copia idéntica a orig.
    RedNodos(const RedNodos& orig);

    // Destructor
    ~RedNodos();

    /* MÉTODOS OBSERVADORES BÁSICOS */

    // EFE: retorna true si 0 <= idVrt < N.
    // NOTA: idVrt significa "identificador de vértice".
    bool xstVrt(int idVrt) const;

    // REQ: 0 <= idVrtO < N && 0 <= idVrtD < N.
    // EFE: retorna true si existe adyacencia entre los vértices idVrtO e idVrtD.
    bool xstAdy(int idVrtO, int idVrtD) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna en "rsp" los identificadores idVrtj de todos los vértices 
    // adyacentes a idVrt en el RedNodos.
    void obtIdVrtAdys(int idVrt, vector< int >& rsp) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna la cantidad de vértices adyacentes a idVrt en el RedNodos.    
    int obtCntVrtAdys(int idVrt) const;

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
    // NOTA: retorna por valor para que NO pueda ser modificado.
    Nodo operator[](int idVrt) const;

    // EFE: retorna el total de vértices en el RedNodos.
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

    /* MÉTODOS MODIFICADORES BÁSICOS */

    // REQ: 0 <= idVrt < N.
    // EFE: retorna el vértice con índice idVrt.
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
    return red_nodos.xstVrt(idVrt);
}

bool RedNodos::xstAdy(int idVrtO, int idVrtD) const {
    return red_nodos.xstAdy(idVrtO, idVrtD);
}

void RedNodos::obtIdVrtAdys(int idVrt, vector< int >& rspRetornar) const {
    red_nodos.obtIdVrtAdys(idVrt, rspRetornar);
}

int RedNodos::obtCntVrtAdys(int idVrt) const {
    return red_nodos.obtCntVrtAdys(idVrt);
}

Nodo RedNodos::operator[](int idVrt) const {
    return red_nodos[idVrt];
}

int RedNodos::obtTotVrt() const {
    return red_nodos.obtTotVrt();
}

int RedNodos::obtTotVrtSusceptibles() const {
    return 0; // sólo para que compile, sustituya con su código
}

int RedNodos::obtTotVrtInfectados() const {
    return 0; // sólo para que compile, sustituya con su código
}

int RedNodos::obtTotVrtResistentes() const {
    return 0; // sólo para que compile, sustituya con su código
}

int RedNodos::obtPrcVrtSusceptibles() const {
    return 0; // sólo para que compile, sustituya con su código
}

int RedNodos::obtPrcVrtInfectados() const {
    return 0; // sólo para que compile, sustituya con su código
}

int RedNodos::obtPrcVrtResistentes() const {
    return 0; // sólo para que compile, sustituya con su código
}

Nodo& RedNodos::operator[](int idVrt) {
    return *(new Nodo()); // sólo para que compile, sustituya con su código
}



