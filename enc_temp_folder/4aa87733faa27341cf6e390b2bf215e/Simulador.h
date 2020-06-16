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
    int contador_tics;
};

Simulador::Simulador(RedNodos& g) : red_nodos(g) {

}

Simulador::~Simulador() {

}

void Simulador::iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc) {
    // Numero de vertices
    int N = red_nodos.obtTotVrt();

    //Asserts
    assert((ios >= 1) && (ios <= N) && (vsc >= 0) && (vsc <= 0.1) && (vcf >= 1) && (vcf <= 20));
    assert((rc >= 0) && (rc <= 0.1) && (grc >= 0) && (grc <= 1));

    // Inicializar atributos de la simulacion 
    this->ios = ios;
    this->vsc = vsc;
    this->vcf = vcf;
    this->rc = rc;
    this->grc = grc;
    this->contador_tics = 0;

    
    // Posicion a infectar generada aleatoriamente
    int pos_infectar;

    // Creaci�n de la distribuci�n probabil�stica uniforme
    random_device rd;
    uniform_int_distribution<int> distribution(0, N); // Entre 0 y N inclusivo
    mt19937 engine(rd()); // Mersenne twister MT19937
    
    // Si ios = N simplemente recorre la red e infecta cada v�rtice
    // en vez de llenar aleatoriamente
    if (ios == N) {
        for (int i = 0; i < N; i++) {
            red_nodos[i].modEstado(Nodo::E::I);
        }
    }
    else {

        // Infeccion de ios v�rtices aleatoriamente con una distribucion uniforme
        for (int i = 0; i < ios; i++) {
            pos_infectar = distribution(engine);

            // Solo se infecta si no ha sido infectado
            if (red_nodos[pos_infectar].obtEstado() == Nodo::E::S) {
                red_nodos[pos_infectar].modEstado(Nodo::E::I);
            }
            else {
                // Si ya fue infectado, resta uno al contador e intenta de nuevo
                i--;
            }
        }
    }


}

void Simulador::simular() {
    // Numero de vertices
    int N = red_nodos.obtTotVrt();

    vector< int > adyacencias;
    int cantAdyacencias;

    // Creaci�n de la distribuci�n probabil�stica uniforme
    std::random_device rd;
    std::uniform_int_distribution<int> distribution(0, 100);
    std::mt19937 engine(rd()); // Mersenne twister MT19937

    // El antivirus revisa los v�rtices cada vcf tics
    bool check_antivirus = (contador_tics % vcf == 0 && contador_tics != 0) ? true : false;

    // Recorre los v�rtices
    for (int id = 0; id < N; id++) {
        red_nodos.obtIdVrtAdys(id, adyacencias);
        cantAdyacencias = red_nodos.obtCntVrtAdys(id);
        // Contagio
        if (red_nodos[id].obtEstado() == Nodo::E::S) {

            // Recorre las adyacencias del v�rtice
            for (int i = 0; i < cantAdyacencias; i++) {

                int idAdy = adyacencias[i];
                // Si hay un vertice infectado
                if (red_nodos[idAdy].obtEstado() == Nodo::E::I) {
                    // Valor aleatorio tomado seg�n la distribuci�n probabilistica
                    int valor = distribution(engine);
                    // El vertice se contagia con una probabilidad de vsc
                    if (valor < (int)(vsc * 100)) {
                        red_nodos[id].modEstado(Nodo::E::I);
                    }
                }
            }
        }
        else if (red_nodos[id].obtEstado() == Nodo::E::I) {
            // Eliminacion de infeccion

            if (check_antivirus) {
                int valor_eliminacion_infeccion = distribution(engine);

                // El vertice se recupera con una probabilidad de rc
                if (valor_eliminacion_infeccion < (int)(rc * 100)) {
                    red_nodos[id].modEstado(Nodo::E::S);

                    // Generacion de resistencia
                    int valor_generacion_resistencia = distribution(engine);
                    // El vertice genera inmunidad con una probabilidad de grc
                    if (valor_generacion_resistencia < (int)(grc * 100)) {
                        red_nodos[id].modEstado(Nodo::E::R);
                    }
                }
            }

            

        }
    }

    // Pas� un tic
    contador_tics++;
}