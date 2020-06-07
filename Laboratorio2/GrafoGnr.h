/*
 * File:   GrafoGnr.h
 * Author: Alan
 *
 * Created on 5 de febrero de 2018, 05:49 PM
 */

#ifndef GRAFOGNR_H
#define GRAFOGNR_H

#include <string>
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
    assert((p > 0) && (p < 1));

    //Llena el vector de v�rtices con N v�rtices
    vectorVrts.resize(N, Vrt< T >());

    // Creaci�n de la distribuci�n probabil�stica uniforme
    std::random_device rd;
    std::uniform_int_distribution<int> distribution(1, 100);
    std::mt19937 engine(rd()); // Mersenne twister MT19937

    // Se asigna memoria a cada v�rtice del vector de v�rtices
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            // Valor tomado seg�n la distribuci�n probabilistica
            int valor = distribution(engine);
 
            // Agrega los vertices en las listas de adyacencia seg�n la probabilidad p
            // Adem�s, no se puede agregar el mismo vertice a su lista de adyacencia
            if (valor < (int)(p * 100) && i != j) {
                vectorVrts[i].lstAdy.push_back(j);
                vectorVrts[j].lstAdy.push_back(i);
            }
        }
    }

    // Se elimina los t�rminos repetidos en cada lista de adyacencia
    for (int i = 0; i < N; i++) {
        vectorVrts[i].lstAdy.sort();
        vectorVrts[i].lstAdy.unique();
    }
}

template < typename T >
GrafoGnr< T >::GrafoGnr(ifstream& archivo) 
{
    // Lee la primera linea del archivo y 
    //llena el vector de vertices con el valor en esa primera linea
    string linea;
    getline(archivo, linea);
    int N = stoi(linea);
    vectorVrts.resize(N, Vrt< T >());
    

    string sublinea;
    int adyacencia;
    int contador = 0; 
    size_t pos;
    size_t fin;
    while (getline(archivo, linea))
    {
        cout << linea << endl;
        while (linea.size() != 0)
        {
            pos = linea.find(',');
            fin = linea.length();
            sublinea = linea.substr(0,pos);
            adyacencia = stoi(sublinea);
            vectorVrts[contador].lstAdy.push_back(adyacencia);
            linea = linea.substr((pos + 1));
            if (pos > fin)
            {
                linea = "";
            }
            else {}
        }
        contador++; 
    }
    archivo.close();
}

template < typename T >
GrafoGnr< T >::GrafoGnr(const GrafoGnr< T >& orig) {
    vectorVrts = orig.vectorVrts;
}

template < typename T >
GrafoGnr< T >::~GrafoGnr() {
}

template < typename T >
bool GrafoGnr< T >::xstVrt(int idVrt) const {
    bool seEncuentraEnGrafo;
    int N = vectorVrts.size();

    if (idVrt >= 0 && idVrt < N)
        seEncuentraEnGrafo = true;
    else
        seEncuentraEnGrafo = false;

    return seEncuentraEnGrafo;
}

template < typename T >
bool GrafoGnr< T >::xstAdy(int idVrtO, int idVrtD) const {
    int N = vectorVrts.size();
    assert((idVrtO >= 0) && (idVrtO < N) && (idVrtD >= 0) && (idVrtD < N));

    bool hayAdyacencia = false;

    // Busca en la lista de adyacencia de vectorVrts[idVrtO] por idVrtD, devolviendo el iterador de este elemento
    auto it = find(vectorVrts[idVrtO].lstAdy.begin(), vectorVrts[idVrtO].lstAdy.end(), idVrtD);

    // Si el iterador apunta al final de la lista, no se encontr�
    if (it != vectorVrts[idVrtO].lstAdy.end())
        hayAdyacencia = true;
    

    return hayAdyacencia;
}

template < typename T >
void GrafoGnr< T >::obtIdVrtAdys(int idVrt, vector< int >& rsp) const {
    int N = vectorVrts.size();
    assert((idVrt >= 0) && (idVrt < N));

    int LstAdysSize = vectorVrts[idVrt].lstAdy.size();
    rsp.resize(LstAdysSize);

    // Copia todos los valores de lstAdy del idVrt a rsp
    std::copy(std::begin(vectorVrts[idVrt].lstAdy), std::end(vectorVrts[idVrt].lstAdy), std::back_inserter(rsp));
    
}

template < typename T >
int GrafoGnr< T >::obtCntVrtAdys(int idVrt) const {
    int N = vectorVrts.size();
    assert((idVrt >= 0) && (idVrt < N));

    int cantAdy = vectorVrts[idVrt].lstAdy.size();
  
    return cantAdy;
}

template < typename T >
T GrafoGnr< T >::operator[](int idVrt) const {
    int N = vectorVrts.size();
    assert((idVrt >= 0) && (idVrt < N));

    T t = vectorVrts[idVrt].t;

    return t;
}

template < typename T >
int GrafoGnr< T >::obtTotArc() const {
    int sumArc = 0;
    int N = vectorVrts.size();

    for (int i = 0; i < N; i++) {

        // Se suma la cuenta de todos los v�rtices adyacentes
        // a cada uno de los v�rtices
        sumArc += vectorVrts[i].size();
    }

    // sumArc siempre es par puesto que en el grafo no dirigido
    // cada v�rtice se conecta "dos veces" a otro v�rtice
    return sumArc/2;
}

template < typename T >
int GrafoGnr< T >::obtTotVrt() const {
    int N = vectorVrts.size();
    return N;
}

template < typename T >
T& GrafoGnr< T >::operator[](int idVrt) {
    int N = vectorVrts.size();
    assert((idVrt >= 0) && (idVrt < N));

    return vectorVrts[idVrt].t;

}

#endif /* GRAFOGNR_H */
