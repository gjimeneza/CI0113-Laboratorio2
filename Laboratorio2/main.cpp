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
// EFE: Lee los datos de un archivo txt y almacena cada linea en un vector 
//      de strings
bool getDocExp(string nombreArchivo, vector < string > vectorStrings);

int main(int argc, char** argv) 
{
        /* El main debera leer y segmentar los datos del experimento, para pedirle al simulador por el metodo iniciarS  imulacion()
        */
        
    vector < string > lista_experimentos;
    
    if (getDocExp("experimentos.txt",lista_experimentos)) 
    {
        ifstream in("nodos_pregenerados.txt");
        RedNodos grafo_simulador(in);
        Simulador sims(grafo_simulador);
        sims.iniciarSimulacion(10,0.05,1,0.05,0.05);
    }
    else 
    {
        cout << "Error";
    }
  
     

    /* 
    RedNodos gNodos(5, 0.5); // se invoca el constructor de redes aleatorias

    cout << gNodos[3] << endl;
    cout << gNodos.obtPrcVrtSusceptibles() << endl;
    /*
    Simulador sim(gNodos); // se crea el simulador pasándole la referencia a la red
    cout << gNodos[0] << endl;*/
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
