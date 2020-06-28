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
#include <exception>
#include <iomanip>
using namespace std;

#include "RedNodos.h"
#include "Simulador.h"
#include "Nodo.h"
#include "GrafoGnr.h"


/*
 * Aca podria definir constantes con los valores posicionales para esas listas [][][]
 */
// MOD: Modifica por valor un vector de strings
// EFE: Lee los datos de un archivo txt y almacena cada linea en un vector de vector
//      de strings
bool getDocExp(string nombreArchivo, vector < vector < string > >& vectorStrings);

// REQ: RedNodos rn construida 
// EFE: Muestra por consola informacion parcial de la red de nodos rn en el tic t
void mostrarConsola(int t, RedNodos rn, int &sum_i, int &sum_s, int &sum_r);

// REQ: RedNodos rn construida
// EFE: Llena un archivo de formato txt con los datos de la simulacion en todos los tiempos!
void llenarArchivo(RedNodos rn, ofstream& file_salida, int tic_actual, int sum_i, int sum_s, int sum_r);

template <typename DATO>
void validarDato(DATO& dato, string dato_string);

// String constante con el nombre del archivo para lectura
string LISTA_EXPERIMENTOS = "experimentos.txt";//"experimentos.txt"; 

int main(int argc, char** argv)
{
    RedNodos grafo_sim(1,0.1);
    /* El main debera leer y segmentar los datos del experimento, para pedirle al simulador por el metodo iniciarSimulacion()
    */
    // Lee datos e inicializa variables necesarias para la simulacion del proximo experimento!
    vector < vector < string > > datos_exp;
    bool condicion_lectura = getDocExp(LISTA_EXPERIMENTOS, datos_exp);
    int condicional, rep_xp, ios, vcf, n_nodos;
    ifstream archivo_nodos;
    double vsc, rc, grc, p_ady;
    string exp_actual;

    for (int num_exp = 0; num_exp < datos_exp.size(); num_exp++)
    {
            // Posicion prederteminada para las variables de la simulacion del experimento?
            // Entre 1 y N
            validarDato(ios, datos_exp[num_exp][0]);
            // Entre 0 y 0.1
            validarDato(vsc, datos_exp[num_exp][1]);
            // Entre 1 y 20 
            validarDato(vcf, datos_exp[num_exp][2]);
            // Entre 0 y 0.1
            validarDato(rc, datos_exp[num_exp][3]);
            // Entre 0 y 0.1
            validarDato(grc, datos_exp[num_exp][4]);
            validarDato(rep_xp, datos_exp[num_exp][5]);
            validarDato(condicional, datos_exp[num_exp][6]);
       
        // Los datos string son numericos
        // Tal vez meter un else para que no siga ejecutando el codigo, si lo guarda aca y creo que esta genial y simplifica el codigo
        if (condicional == 1)
        {
            validarDato(n_nodos, datos_exp[num_exp][7]);
            validarDato(p_ady, datos_exp[num_exp][8]);
            RedNodos grafo1(n_nodos, p_ady);
            grafo_sim = grafo1;
        }
        else
        {
            if (condicional == 2)
            {
                ifstream in(datos_exp[num_exp][7].c_str());
                RedNodos grafo2(in);
                grafo_sim = grafo2;
            }
        }
        // Genera un respaldo del grafo inicial para realizar la simulacion sobre el mismo grafo 
        // las veces necesarias
        RedNodos respaldo_repeticiones = grafo_sim;
        if ((condicional != -1) && (ios >= 1) && (ios <= grafo_sim.obtTotVrt()) && (vsc >= 0) && (vsc <= 0.1) && (vcf >= 1) && (vsc <= 20) && (rc >= 0) && (rc <= 0.1) && (grc >= 0) && (grc <= 1))
        {
            grafo_sim.obtTotVrt();
            Simulador sims(grafo_sim);

            // Crea un archivo donde almacenar las salidas de la simulacion con un nombre que el usuario le asigne
            string archivo_salida_name;
            cout << "Digite un nombre para el archivo graficable" << endl;
            cin >> archivo_salida_name;

            // Ejecuta la simulacion el numero de repeticiones solicitado!
            for (int repeticion = 0; repeticion < rep_xp; repeticion++)
            {
                int sumatoria_infectados = 0; int sumatoria_susceptibles = 0; int sumatoria_resistentes = 0;
                //Agrega una serie numerica al nombre para las repeticiones
                string archivo_salida_rep = archivo_salida_name;
                archivo_salida_rep += to_string(repeticion);
                archivo_salida_rep += ".txt";
                ofstream archivo_graficable(archivo_salida_rep.c_str());

                // Llena la primera fila del archivo con el nombre de cada columna 
                archivo_graficable << "Numero Infectados,Porcentaje Infectados,Promedio Infectados,Numero Susceptibles,"
                    << "Porcentaje Susceptibles,Promedio Susceptibles,Numero Resistentes,Porcentaje Resistentes,Promedio Resistentes" << endl;

                // Realiza la simulacion el numero de veces que sea necesario hasta que el numero de infectados sea 0 
                int tic = 0;
                
                sims.iniciarSimulacion(ios, vsc, vcf, rc, grc);
                mostrarConsola(tic, grafo_sim, sumatoria_infectados, sumatoria_susceptibles, sumatoria_resistentes);
                llenarArchivo(grafo_sim, archivo_graficable, tic, sumatoria_infectados, sumatoria_susceptibles, sumatoria_resistentes);
                while (!(grafo_sim.obtTotVrtInfectados() == 0))
                {
                    tic++;
                    sims.simular();
                    mostrarConsola(tic, grafo_sim, sumatoria_infectados, sumatoria_susceptibles, sumatoria_resistentes);
                    llenarArchivo(grafo_sim, archivo_graficable, tic, sumatoria_infectados, sumatoria_susceptibles, sumatoria_resistentes);
                }
                mostrarConsola(tic, grafo_sim, sumatoria_infectados, sumatoria_susceptibles, sumatoria_resistentes);
                llenarArchivo(grafo_sim, archivo_graficable, tic, sumatoria_infectados, sumatoria_susceptibles, sumatoria_resistentes);
                archivo_graficable.close();
                // Asigna la copia de seguridad del grafo iniciar para repetir el experimento
                grafo_sim = respaldo_repeticiones;
            }
            system("pause");
        }
        else
        {
            // Consultar que tal esto para agregar!! 
            cerr << "Error: Valor invalido o fuera de rango" << endl;
            system("pause");
        }
    }
    // Destructores
    
    return 0;
}

bool getDocExp(string nombreArchivo, vector < vector < string > >& vectorStrings)
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
        int num_exp = 0;
        string linea_experimento;
        while (getline(in, linea_experimento))
        {
            int pos_esp = 0;
            int pos_dato = 0;
            vector <string> exp;
            vectorStrings.push_back(exp);
            while (linea_experimento.size() > 0)
            {
                pos_esp = linea_experimento.find(' ');
                string aux = linea_experimento.substr(0, pos_esp);
                vectorStrings[num_exp].push_back(aux);
                linea_experimento = linea_experimento.substr(pos_esp + 1);
                pos_dato++;
                if (pos_esp > linea_experimento.size())
                {
                    linea_experimento = "";
                }
            }
            num_exp++;
        }
        verificacion = true;
    }
    return verificacion;
}

void mostrarConsola(int t, RedNodos rn, int& sum_i, int& sum_s, int& sum_r)
{
    // Para imprimir los datos antes de empezar la simulacion
    if (t == 0)
    {
        cout << "INFORMACION EN TIC #" << t << endl;
        // INFECTADOS
        cout << "Infectados: " << endl;
        cout << "Total: " << rn.obtTotVrtInfectados() << endl;
        cout << "Porcentaje: " << setprecision(3) << rn.obtPrcVrtInfectados() << endl;// Porcentaje
        cout << "Promedio: " << rn.obtTotVrtInfectados();

        // SUSCEPTIBLES
        cout << "Infectados: " << endl;
        cout << "Total: " << rn.obtTotVrtSusceptibles() << endl;
        cout << "Porcentaje: " << setprecision(3) << rn.obtPrcVrtSusceptibles() << endl;// Porcentaje
        cout << "Promedio: " << rn.obtTotVrtSusceptibles();

        // RESISTENTES
        cout << "Infectados: " << endl;
        cout << "Total: " << rn.obtTotVrtResistentes() << endl;
        cout << "Porcentaje: " << setprecision(3) << rn.obtPrcVrtResistentes() << endl;// Porcentaje
        cout << "Promedio: " << rn.obtTotVrtResistentes();
    }
    else
    {
        sum_i += rn.obtTotVrtInfectados();
        sum_s += rn.obtTotVrtSusceptibles();
        sum_r += rn.obtTotVrtResistentes();
        // Genera salida por consola
        if (rn.obtTotVrtInfectados() != 0)
        {
            cout << "INFORMACION EN TIC #" << t << endl;
            // INFECTADOS
            cout << "Infectados: " << endl;
            cout << "Total: " << rn.obtTotVrtInfectados() << endl;
            cout << "Porcentaje: " << setprecision(3) << rn.obtPrcVrtInfectados() << endl;// Porcentaje
            cout << "Promedio: " << setprecision(3) << sum_i / double(t) << endl; // Promedio 
        }
        else
        {
            cout << "INFORMACION AL FINALIZAR LA SIMULACION" << endl;
            // TIEMPO NECESARIO 
            cout << "Para estabilizar la red fueron necesarios " << t << "tics." << endl;
        }

        // SUSCEPTIBLES
        cout << "Susceptibles: " << endl;
        cout << "Total: " << rn.obtTotVrtSusceptibles() << endl;
        cout << "Porcentaje: " << setprecision(3) << rn.obtPrcVrtSusceptibles() << endl;// Porcentaje
        cout << "Promedio: " << setprecision(3) << sum_s / double(t) << endl; // Promedio 

        //RESISTENTES
        cout << "Resistencias: " << endl;
        cout << "Total: " << rn.obtTotVrtResistentes() << endl;
        cout << "Porcentaje: " << setprecision(3) << rn.obtPrcVrtResistentes() << endl;// Porcentaje
        cout << "Promedio: " << setprecision(3) << sum_r / double(t) << endl; // Promedio
    }
}

void llenarArchivo(RedNodos rn, ofstream& file_salida, int tic_actual, int sum_i, int sum_s, int sum_r)
{    // Datos para el archivo con el siguiente formato
    // tic,#I,%I,promI,#S,%S,promS,#R,%R,promR
    if (tic_actual == 0)
    {
        // INFECTADOS // pendiente agregar escritura
        file_salida << rn.obtTotVrtInfectados() << "," << setprecision(3) << rn.obtPrcVrtInfectados()
            << "," << rn.obtTotVrtInfectados() << ",";
        // SUSCEPTIBLES 
        file_salida << rn.obtTotVrtSusceptibles() << "," << setprecision(3) << rn.obtPrcVrtSusceptibles()
            << "," << rn.obtTotVrtSusceptibles() << ",";
        // RESISTENTES
        file_salida << rn.obtTotVrtResistentes() << "," << setprecision(3) << rn.obtPrcVrtResistentes()
            << "," << rn.obtTotVrtResistentes() << endl;
    }
    else
    {
        if (rn.obtTotVrtInfectados() != 0)
        {
            // INFECTADOS // pendiente agregar escritura
            file_salida << rn.obtTotVrtInfectados() << "," << setprecision(3) << rn.obtPrcVrtInfectados()
                << "," << setprecision(3) << sum_i / double(tic_actual) << ",";
        }
        else
        {
            // Agregar datos al finalizar para columnas de infectados
            file_salida << "0,0,0,";
        }
        // SUSCEPTIBLES 
        file_salida << rn.obtTotVrtSusceptibles() << "," << setprecision(3) << rn.obtPrcVrtSusceptibles()
            << "," << setprecision(3) << sum_s / double(tic_actual) << ",";
        // RESISTENTES
        file_salida << rn.obtTotVrtResistentes() << "," << setprecision(3) << rn.obtPrcVrtResistentes()
            << "," << setprecision(3) << sum_r / double(tic_actual) << endl;
    }
}


template <typename DATO>
void validarDato(DATO& dato, string dato_string)
{
    // Intenta convertir la string en un double
    try
    {
        dato = stod(dato_string);
    }
    catch (exception e)
    {
        // Si falla se torna -1 
        dato = -1;
    }
}