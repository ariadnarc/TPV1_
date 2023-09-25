#include<iostream>
#include "ListaCoches.h"
#include <fstream>

using namespace std;


int ListaCoches::BuscarCoche(int codigo) {
    
    int cotaInferior = 0, cotaSuperior = numElementos, valorMedio = cotaSuperior / 2, resultado = -1;
    bool encontrado = false;
    while (!encontrado && cotaInferior <= cotaSuperior && valorMedio >= 0 && valorMedio < numElementos)
    {
        if (codigo == lista[valorMedio]->codigo)
        {
            resultado = valorMedio;
            encontrado = true;
        }
        else
        {
            if (codigo > lista[valorMedio]->codigo)
            {
                cotaInferior = valorMedio + 1;
                valorMedio = (cotaSuperior + cotaInferior) / 2;
            }
            else
            {
                cotaSuperior = valorMedio - 1;
                valorMedio = (cotaSuperior + cotaInferior) / 2;
            }
        }
    }
    return resultado;
    
}




bool ListaCoches::LeerModelos()
{
    ifstream entrada("coches.txt");

    if (!entrada.is_open()) {
        cout << "ERROR";
        return false;
    }

    entrada >> numElementos;

    size = numElementos + 10;

    lista = new Coche* [size];

    for (int i = 0; i < numElementos; i++)
    {
        Coche* Cocheaux = new Coche();

        lista[i] = Cocheaux;

        entrada >> lista[i]->codigo;
        entrada >> lista[i]->precioDia;
        entrada >> lista[i]->marca;

        string aux;
        entrada >> aux;
        lista[i]->marca += " " + aux;

    }

    return true;
}



Coche* ListaCoches::GetCoche(int index) {
    return lista[index];
}


void ListaCoches::LimpiarMemoria() {

    for (int i = 0; i < numElementos; i++) {
        delete lista[i];
    }

    delete[] lista;
}