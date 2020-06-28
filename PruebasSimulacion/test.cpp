#include "pch.h"
#include "pch.h"
#include "../Laboratorio2/RedNodos.h"
#include "../Laboratorio2/Simulador.h"
#include <string>
#include <fstream>

class PruebasRedNodos : public ::testing::Test
{
protected: 
    /* DATOS COMUNES PARA TODAS LAS PRUEBAS */
    
    //Constructor inicializador del suite de pruebas
    PruebasRedNodos();

    // Destructor del suite de pruebas
    ~PruebasRedNodos();

};
// Red de nodos con 10 vertices
string nombre_peq = "C://Proyectos/LabGUI 2/CI0113-Laboratorio2/Laboratorio2/redMuyPeq.txt";
ifstream archivo_peq(nombre_peq.c_str());
RedNodos rnp_small_file(archivo_peq);

// Red de nodos con 100 vertices
string nombre_big = "C://Proyectos/LabGUI 2/CI0113-Laboratorio2/Laboratorio2/redPeq.txt";
ifstream archivo_big(nombre_big.c_str());
RedNodos rnp_big_file(archivo_big);

// DEFINICION DE LOS METODOS BASICOS DEL ACCESORIO
PruebasRedNodos::PruebasRedNodos(){
}

PruebasRedNodos::~PruebasRedNodos(){
}

// CASOS PRUEBA 
// EFE: Verificar cantidad de nodos y de aristas con la red muy pequeña de 10 nodos
TEST_F(PruebasRedNodos, inicializacionCorrecta_archivo_1)
{
    // Cantidad de vertices de la red
    ASSERT_EQ(rnp_small_file.obtTotVrt(), 10);

    // Cantidad de adyacencias por nodo
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(0), 2);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(1), 3);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(2), 3);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(3), 2);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(4), 6);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(5), 4);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(6), 2);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(7), 4);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(8), 3);
    ASSERT_EQ(rnp_small_file.obtCntVrtAdys(9), 5);
    
}
// EFE: Verificar cantidad de nodos y de aristas con la red pequeña de 100 nodos
TEST_F(PruebasRedNodos, inicializacionCorrecta_archivo_2)
{
    // Cantidad de vertices de la red
    ASSERT_EQ(rnp_big_file.obtTotVrt(), 100);
    
    // Cantidad de adyacencias para algunos casos de nodos 
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(0), 7);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(1), 10);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(3), 1);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(48), 8);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(60), 20);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(90), 2);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(99), 20);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(91), 3);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(36), 7);
    ASSERT_EQ(rnp_big_file.obtCntVrtAdys(49), 8);

}


// EFE: Prueba el metodo xstVrt cuando el nodo no existe
TEST_F(PruebasRedNodos, xstVrt_1)
{
    // Se consulta un nodo que no existe 
    EXPECT_FALSE(rnp_small_file.xstVrt(10));
    EXPECT_FALSE(rnp_small_file.xstVrt(11));
    EXPECT_FALSE(rnp_small_file.xstVrt(100));
    EXPECT_FALSE(rnp_small_file.xstVrt(50));
}

// EFE: Prueba el metodo xstVrt cuando el nodo existe
TEST_F(PruebasRedNodos, xstVrt_2) 
{
    EXPECT_TRUE(rnp_small_file.xstVrt(0));
    EXPECT_TRUE(rnp_small_file.xstVrt(1));
    EXPECT_TRUE(rnp_small_file.xstVrt(2));
    EXPECT_TRUE(rnp_small_file.xstVrt(3));
    EXPECT_TRUE(rnp_small_file.xstVrt(4));
    EXPECT_TRUE(rnp_small_file.xstVrt(5));
    EXPECT_TRUE(rnp_small_file.xstVrt(6));
    EXPECT_TRUE(rnp_small_file.xstVrt(7));
    EXPECT_TRUE(rnp_small_file.xstVrt(8));
    EXPECT_TRUE(rnp_small_file.xstVrt(9));
}

// EFE: Prueba el metodo xstVrt cuando la arista no existe
TEST_F(PruebasRedNodos, xstAdy_1)
{
    // Adyacencias no existentes en la red de 10 nodos 
    EXPECT_FALSE(rnp_small_file.xstAdy(2, 6));
    EXPECT_FALSE(rnp_small_file.xstAdy(0, 1));
    EXPECT_FALSE(rnp_small_file.xstAdy(9, 9));
    EXPECT_FALSE(rnp_small_file.xstAdy(5, 8));

}

// EFE: Prueba el metodo xstVrt cuando la arista existe
TEST_F(PruebasRedNodos, xstAdy_2)
{
    // Adyacencias existentes para la red de 10 nodos
    EXPECT_TRUE(rnp_small_file.xstAdy(0,7));
    EXPECT_TRUE(rnp_small_file.xstAdy(1,8));
    EXPECT_TRUE(rnp_small_file.xstAdy(2,4));
    EXPECT_TRUE(rnp_small_file.xstAdy(3,9));
    EXPECT_TRUE(rnp_small_file.xstAdy(5,7));
    EXPECT_TRUE(rnp_small_file.xstAdy(7,4)); 
    EXPECT_TRUE(rnp_small_file.xstAdy(9,3));
}


// Red de nodos con 10 vertices modificado para las siguientes pruebas 
string nombre_mod = "C://Proyectos/LabGUI 2/CI0113-Laboratorio2/Laboratorio2/redMod.txt";
ifstream archivo_mod(nombre_mod.c_str());
RedNodos rnp_mod(archivo_mod);


// EFE: Comprueba que el vector nodos adyacentes
//      cuando este se encuentra vacio, NO hay arista
TEST_F(PruebasRedNodos, obtIdAdy_1)
{
    // De la redMuyPeq se eliminaron las adyacencias del nodo 3 como caso con 0 adys.
    //      ademas de eliminar las adys de los otros nodos con el nodo 3. redMod.txt
    vector <int> vector_pruebas;
    rnp_mod.obtIdVrtAdys(3, vector_pruebas);

    // Se compara con un vector vacio
    vector <int> vector_esperado = { };
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // VERIFICA QUE EL TAMAÑO DEL VECTOR SEA 0
    EXPECT_EQ(vector_pruebas.size(),0);
}

// EFE: Comprueba que el vector nodos adyacentes
//      cuando tiene una SOLA arista
TEST_F(PruebasRedNodos, obtIdAdy_2)
{
    // De la redMuyPeq se eliminaron algunas adyacencias del nodo 0 como caso con 1 
    //      adys, ademas de eliminar la correspondiente del nodo esa arista. redMod.txt
    vector <int> vector_pruebas;
    rnp_mod.obtIdVrtAdys(0, vector_pruebas);
    vector <int> vector_esperado = { 7 };
    EXPECT_EQ(vector_pruebas, vector_esperado);

}

// EFE: Comprueba que el vector nodos adyacentes
//      cuando tiene mas de una arista
TEST_F(PruebasRedNodos, obtIdAdy_3)
{
   // Se prueba uno de los nodos modificados, mas concretamente el nodo 4, el mismo
   //      prierde una arista por la adyacencia con el nodo 3
    // NODO 4
    vector <int> vector_pruebas;
    rnp_mod.obtIdVrtAdys(4, vector_pruebas);
    vector <int> vector_esperado = { 2, 5, 6, 7, 8 };
    EXPECT_EQ(vector_pruebas, vector_esperado);
    
    // NODO 1
    rnp_mod.obtIdVrtAdys(1, vector_pruebas);
    vector_esperado = { 7, 8, 9 };
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // NODO 2
    rnp_mod.obtIdVrtAdys(2, vector_pruebas);
    vector_esperado = { 4, 5, 9 };
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // NODO 5
    rnp_mod.obtIdVrtAdys(5, vector_pruebas);
    vector_esperado = { 2, 4, 7, 9 };
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // NODO 6
    rnp_mod.obtIdVrtAdys(6, vector_pruebas);
    vector_esperado = { 4, 9};
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // NODO 7 
    rnp_mod.obtIdVrtAdys(7, vector_pruebas);
    vector_esperado = { 0, 1, 4, 5 };
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // NODO 8 
    rnp_mod.obtIdVrtAdys(8, vector_pruebas);
    vector_esperado = { 1, 4 };
    EXPECT_EQ(vector_pruebas, vector_esperado);

    // NODO 9
    rnp_mod.obtIdVrtAdys(9, vector_pruebas);
    vector_esperado = { 1, 2, 5, 6 };
    EXPECT_EQ(vector_pruebas, vector_esperado);
}

// EFE: Verifica que la cantidad de aristas desde un nodo es la correcta 
//      cuando no tiene arista
TEST_F(PruebasRedNodos, obtCantAdys_1) 
{
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(3),0);

}
// EFE: Verifica que la cantidad de aristas desde un nodo es la correcta 
//      cuando tiene SOLO una arista
TEST_F(PruebasRedNodos, obtCantAdys_2)
{
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(0),1);
}

// EFE: Verifica que la cantidad de aristas desde un nodo es la correcta 
//      cuando tiene mas de una arista
TEST_F(PruebasRedNodos, obtCantAdys_3)
{
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(1),3);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(2),3);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(4),5);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(5),4);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(6),2);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(7),4);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(8),2);
    EXPECT_EQ(rnp_mod.obtCntVrtAdys(9),4);
}

