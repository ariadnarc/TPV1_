#include<iostream>
#include<fstream>
#include "ListaAlquileres.h"
#include<algorithm>

using namespace std;


void ListaAlquileres::MostrarAlquileres()
{
    for (int i = 0; i < numElementos; i++)
    {
        //referencia, muy util
        const Alquiler& alq = lista[i];

        if (alq.coche == nullptr)
        {
            cout << alq.fecha << " " << "ERROR: modelo inexistente." << endl;
        }
        else
        {
            cout << alq.fecha << " " << alq.coche->marca << " " << alq.dias << " día(s) por " 
                << alq.dias * alq.coche->precioDia << " euros." << endl;
        }
    }
}



bool ListaAlquileres::LeerAlquileres(ListaCoches& listaC)
{
    ifstream entrada("rent.txt");

    if (!entrada.is_open()) {
        cout << "ERROR";
        return false;
    }

    entrada >> numElementos;

    size = numElementos + 10;

    lista = new Alquiler[size];

    for (int i = 0; i < numElementos; i++)
    {
        int codigo;
        entrada >> codigo;

        int indiceCoche = listaC.BuscarCoche(codigo);

        if (indiceCoche == -1)
        {
            lista[i].coche = nullptr;
        }
        else
        {
            lista[i].coche = listaC.GetCoche(indiceCoche);
        }


        // flujo de entrada
        entrada >> lista[i].fecha
                >> lista[i].dias;


    }

    return true;
}


void ListaAlquileres:: OrdenarAlquileres()
{
    sort(lista, lista + numElementos);
}


void ListaAlquileres::LimpiarMemoria() {
    delete[] lista;
}