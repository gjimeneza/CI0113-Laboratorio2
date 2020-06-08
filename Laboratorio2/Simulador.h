#pragma once

#include "RedNodos.h"
#include "Nodo.h"
#include <time.h>
#include <stdlib.h>
#include <iomanip>

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

    // Cambia el estado de los nodos en base al atributo ios
    while ((contador < ios)) 
    {
        // Tome el codigo de la clase GrafosGnr 
        // Aunque no se como funciona 
        random_device rd;
        uniform_int_distribution<int> distribution(0,99);
        mt19937 engine(rd());
        pos_infectar = distribution(engine);

        // Si la posicion existe comprueba el estado, si la posicion no existe sale directamente y no comprueba el estado 
        if (red_nodos.xstVrt(pos_infectar) && (red_nodos[pos_infectar].obtEstado() != Nodo::E::I))
        {
            red_nodos[pos_infectar].modEstado(Nodo::E::I);
            contador++;
        }
        else {}

    }
}

void Simulador::simular() 
{
    // Para las probabilidades por turno pienso en generar numeros enteros al azar y dividir entre 100
    //Necesito generar una copia de red_nodos, pero no del simulador, para mantener el estado 

    int ciclo = 0;
    while (red_nodos.obtTotVrtInfectados() > 0) 
    {
        ciclo++;
        for (int i = 0; i < red_nodos.obtTotVrt(); i++) 
        {
            bool existe = red_nodos.xstVrt(i);
            if (red_nodos[i].obtEstado()!=Nodo::E::R) 
            {
                if (red_nodos[i].obtEstado() == Nodo::E::S) 
                {
                    int apuntador = 0; 
                    vector <int> ady_actuales;
                    red_nodos.obtIdVrtAdys(i, ady_actuales);
                    
                    while ((apuntador < ady_actuales.size()) && (red_nodos.xstVrt(ady_actuales[apuntador])))
                    {
                        if ((red_nodos[apuntador].obtEstado == Nodo::E::I) && (rollDice() < vsc)) 
                        {
                            red_nodos[i].modEstado(Nodo::E::I);
                        }
                        else 
                        {
                        }
                        apuntador++;
                    }
                }
                else 
                {
                    if ((ciclo%vcf == 0) && (rollDice() < rc)) 
                    {
                        red_nodos[i].modEstado(Nodo::E::S);
                        if (rollDice() < grc) 
                        {
                            red_nodos[i].modEstado(Nodo::E::R);
                        }
                    }
                    else {}
                }
            }
            else 
            {
            }
        }
    }
}

double rollDice()
{

}
