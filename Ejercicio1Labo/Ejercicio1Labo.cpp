// Samuel García Bazán
// Ariadna Alicia Ruiz Castillo
// Grupo 15

#include <iostream>
#include <fstream>
#include <Windows.h>
#include "ListaAlquileres.h" //llamadas recursivas a los otros includes

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    ListaCoches listaC;
    ListaAlquileres listaA;

    listaC.LeerModelos();

    listaA.LeerAlquileres(listaC);

    listaA.OrdenarAlquileres();

    listaA.MostrarAlquileres();

    // limpiar la memoria
    
    listaC.LimpiarMemoria();
    listaA.LimpiarMemoria();

    
}