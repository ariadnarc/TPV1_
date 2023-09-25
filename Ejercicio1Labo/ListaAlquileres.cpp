#include<iostream>
#include<fstream>
#include "ListaAlquileres.h"
#include<algorithm>

using namespace std;


void ListaAlquileres::MostrarAlquileres()
{
    for (int i = 0; i < numElementos; i++)
    {        
        if (lista[i].coche == nullptr)
        {
            cout << lista[i].fecha << " " << "ERROR: modelo inexistente." << endl;
        }
        else
        {
            cout << lista[i].fecha << " " << lista[i].coche->marca << " " << lista[i].dias << " día(s) por " 
                << lista[i].dias * lista[i].coche->precioDia << " euros." << endl;
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

        entrada >> lista[i].fecha;

        entrada >> lista[i].dias;


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