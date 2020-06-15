#pragma once

#include "RedNodos.h"
#include "Nodo.h"
#include <time.h>
#include <stdlib.h>
#include <iomanip>
#include <exception>

class Simulador {
    // Representa el proceso de simulación de la infección en la red de computadoras.

public:

    // EFE: Construye un simulador que transformará al grafo g.
    Simulador(RedNodos& g);

    // Destruye a *this retornando toda la memoria asignada dinámicamente.
    ~Simulador();


    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado.    
    // EFE: inicializa el simulador con los siguientes parámetros:
    //      ios o initial-outbreak-size [1..N], N cantidad de vértices: cantidad
    //           de vértices contagiados al comienzo de la simulación.
    //      vsc o virus-spread-chance [0..0.1]: probabilidad de contagio.
    //      vcf o virus-check-frecuency [1..20]: frecuencia de chequeo antivirus.
    //      rc o recovery-chance [0..0.1]: probabilidad de eliminación de infección.
    //      grc o gain-resistance-chance [0..1]: probabilidad de generar resistencia.   
    void iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc);

    // REQ: el grafo asociado (el pasado al constructor) esté bien construido.
    // MOD: el grafo asociado.
    // EFE: aplica al grafo asociado una transformación con base en las reglas de 
    //      la simulación especificadas.
    void simular();

private:
    RedNodos& red_nodos;
    int ios;
    double vsc;
    int vcf;
    double rc;
    double grc;
    int contador_tics;

    // Genera un numero al azar
    double rollDice();
};

Simulador::Simulador(RedNodos& g) : red_nodos(g) 
{

}

Simulador::~Simulador() {

}
// Para algunos pasos del metodo agrege no se si se puede #include <time.h> #include <stdlib.h> #include <iomanip> hay que preguntar
void Simulador::iniciarSimulacion(int ios, double vsc, int vcf, double rc, double grc) 
{
    // Numero de nodos
    int N = red_nodos.obtTotVrt();
    // INCLUIR ASSERT, pero no se si con los limites de arriba 

    // Inicializar atributos de la simulacion 
    Simulador::ios = ios;
    Simulador::vsc = vsc; 
    Simulador::vcf = vcf;
    Simulador::rc = rc;
    Simulador::grc = grc;

    int contador = 0; 
    // Posicion a infectar generada aleatoriamente
    int pos_infectar;

    // Cambia el estado de los nodos en base al atributo ios]
    // Tome el codigo de la clase GrafosGnr 
    // Aunque no se como funciona 
    random_device rd;
    uniform_int_distribution<int> distribution(0, (N-1));
    mt19937 engine(rd());
    
    while ((contador < ios)) 
    {
        pos_infectar = distribution(engine);

        // Si la posicion existe comprueba el estado, si la posicion no existe sale directamente y no comprueba el estado 
        if (red_nodos.xstVrt(pos_infectar) && (red_nodos[pos_infectar].obtEstado() != 1))
        {
            red_nodos[pos_infectar].modEstado(Nodo::E::I);
            contador++;
        }
        else {}
    }

}

void Simulador::simular() 
{
    // Numero de vertices
    int N = red_nodos.obtTotVrt();

    vector< int > adyacencias;
    int cantAdyacencias;

    // Creación de la distribución probabilística uniforme
    std::random_device rd;
    std::uniform_int_distribution<int> distribution(0, 100);
    std::mt19937 engine(rd()); // Mersenne twister MT19937

    // El antivirus revisa los vértices cada vcf tics
    bool check_antivirus = (contador_tics % vcf == 0 && contador_tics != 0) ? true : false;

    // Recorre los vértices
    for (int id = 0; id < N; id++) {
        red_nodos.obtIdVrtAdys(id, adyacencias);
        cantAdyacencias = red_nodos.obtCntVrtAdys(id);
        // Contagio
        if (red_nodos[id].obtEstado() == Nodo::E::S) {

            // Recorre las adyacencias del vértice
            for (int i = 0; i < cantAdyacencias; i++) {

                int idAdy = adyacencias[i];
                // Si hay un vertice infectado
                if (red_nodos[idAdy].obtEstado() == Nodo::E::I) {
                    // Valor aleatorio tomado según la distribución probabilistica
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

    // Pasó un tic
    contador_tics++;
}

double rollDice()
{
    random_device rd;
    uniform_int_distribution<int> distribution(1, 100);
    mt19937 engine(rd());

    double probabilidad = distribution(engine);
    probabilidad /= 100;
    cout << probabilidad;
    return probabilidad;
}
