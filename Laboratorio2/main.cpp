/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

 /*
  * File:   main.cpp
  * Author: Alan
  *
  * Created on 11 de septiembre de 2018, 05:36 PM
  */

#include <iostream>
using namespace std;

#include "RedNodos.h"
#include "Simulador.h"
#include "Nodo.h"
#include "GrafoGnr.h"
/*
 *
 */
// MOD: Modifica por valor un vector de strings
// REQ: nombreArchivo && vector de hileras exista
// EFE: Lee los datos de un archivo txt y almacena cada linea en un vector 
//      de strings
bool getDocExp(string nombreArchivo, vector < string > vectorStrings);

int main(int argc, char** argv) 
{
    //vector < string > lista_experimentos;
    //
    //if (getDocExp("experimentos.txt",lista_experimentos)) 
    //{
    //    ifstream in("nodos_pregenerados.txt");
    //    GrafoGnr < int > grafo(in);
    //}
    //else 
    //{
    //    cout << "Error";
    //}

   

    
    RedNodos gNodos(150, 0.5); // se invoca el constructor de redes aleatorias

    Simulador sim(gNodos); // se crea el simulador pasándole la referencia a la red

    sim.iniciarSimulacion(10, 0.01, 3, 0.05, 0.2);

    cout << "Total: " << gNodos.obtTotVrt() << endl;

    for (int i = 0; i < 200; i++) {
        cout << "Tic: " << i << endl;
        cout << "Total susceptibles: " << gNodos.obtTotVrtSusceptibles() << endl;
        cout << "Total infectados: " << gNodos.obtTotVrtInfectados() << endl;
        cout << "Total resistentes: " << gNodos.obtTotVrtResistentes() << endl;

        sim.simular();
    }
    
    /*
    GrafoGnr< int > g_ints(10, 0.5);

    for (int i = 0; i < 10; i++)
        cout << g_ints[i] << ',';
    cout << endl;
    */
    return 0;
}

bool getDocExp(string nombreArchivo, vector < string > vectorStrings)
{
    ifstream in(nombreArchivo.c_str());
    bool verificacion;
    if (!in)
    {
        cerr << "NO se ha podido abrir el archivo " << nombreArchivo << endl;
        verificacion = false;
    }
    else
    {
        string linea_experimento;
        while (getline(in, linea_experimento))
        {
            if (linea_experimento.size() > 0)
            {
                vectorStrings.push_back(linea_experimento);
            }
        }
        verificacion = true;
    }

    return verificacion;
}
