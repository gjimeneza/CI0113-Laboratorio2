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
int main(int argc, char** argv) {
    /*
    RedNodos gNodos(5,0.5); // se invoca el constructor de redes aleatorias
    Simulador sim(gNodos); // se crea el simulador pasándole la referencia a la red
    cout << gNodos[0] << endl;*/

    GrafoGnr< int > g_ints(10, 0.5);
    for (int i = 0; i < 10; i++)
        cout << g_ints[i] << ',';
    cout << endl;

    return 0;
}

