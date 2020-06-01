#pragma once

#include "RedNodos.h"
#include "Nodo.h"

class Simulador {
    // Representa el proceso de simulaci�n de la infecci�n en la red de computadoras.

public:

    // EFE: Construye un simulador que transformar� al grafo g.
    Simulador(RedNodos& g);

    // Destruye a *this retornando toda la memoria asignada din�micamente.
    ~Simulador();


    // REQ: el grafo asociado (el pasado al constructor) est� bien construido.
    // MOD: el grafo asociado.    
    // EFE: inicializa el simulador con los siguientes par�metros:
    //      ios o initial-outbreak-size [1..N], N cantidad de v�rtices: cantidad
    //           de v�rtices contagiados al comienzo de la simulaci�n.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de contagio.
    //      vcf o virus-check-frecuency [1..20]: frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de eliminaci�n de infecci�n.
    //      grc o gain-resistance-chance [0..1]: probabilidad de generar resistencia.   
    void iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc);

    // REQ: el grafo asociado (el pasado al constructor) est� bien construido.
    // MOD: el grafo asociado.
    // EFE: aplica al grafo asociado una transformaci�n con base en las reglas de 
    //      la simulaci�n especificadas.
    void simular();

private:
    RedNodos& red_nodos;
    int ios;
    double vsc;
    int vcf;
    double rc;
    double grc;
};

Simulador::Simulador(RedNodos& g) : red_nodos(g) {

}

Simulador::~Simulador() {

}

void Simulador::iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc) {

}

void Simulador::simular() {

}