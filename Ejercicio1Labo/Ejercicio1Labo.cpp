// Samuel García Bazán
// Ariadna Alicia Ruiz Castillo
// Grupo 15

#include <iostream>
#include "Date.h"
#include <fstream>
#include <Windows.h>
#include <algorithm>

using namespace std;

struct Coche
{
    int codigo, precioDia;
    string marca;
};

struct Alquiler
{
    Coche* coche;
    Date fecha;
    int dias;
};

struct ListaCoches
{
    Coche* lista;
    int size, numElementos;
};

struct ListaAlquileres
{
    Alquiler* lista;
    int size, numElementos;
};

int BuscarCoche(int codigo, const ListaCoches& listaCoches)
{
    int cotaInferior = 0, cotaSuperior = listaCoches.numElementos, valorMedio = cotaSuperior/2, resultado = -1;
    bool encontrado = false;
    while (!encontrado && cotaInferior <= cotaSuperior) 
    {
        if (codigo == listaCoches.lista[valorMedio].codigo) 
        {
            resultado = valorMedio;
            encontrado = true;
        }
        else 
        {
            if (codigo > listaCoches.lista[valorMedio].codigo) 
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

void MostrarAlquileres(const ListaAlquileres& listaAlq) 
{
    for (int i = 0; i < listaAlq.numElementos; i++) 
    {
        
        if (listaAlq.lista[i].coche == nullptr) 
        {
            cout << listaAlq.lista[i].fecha << " " << "ERROR: modelo inexistente." << endl;

        }
        else 
        {
             cout << listaAlq.lista[i].fecha << " " << listaAlq.lista[i].coche->marca << " " << listaAlq.lista[i].dias << " día(s) por " << listaAlq.lista[i].dias * listaAlq.lista[i].coche->precioDia << " euros." << endl;

        }
    }
}

bool LeerModelos(ListaCoches& listaC)
{
    ifstream entrada("coches.txt");

    if (!entrada.is_open()) {
        cout << "ERROR";
        return false;
    }

    entrada >> listaC.numElementos;

    listaC.size = listaC.numElementos + 10;

    listaC.lista = new Coche[listaC.size];

    for (int i = 0; i < listaC.numElementos; i++)
    {
        entrada >> listaC.lista[i].codigo;
        entrada >> listaC.lista[i].precioDia;
        entrada >> listaC.lista[i].marca;

        string aux;
        entrada >> aux;
        listaC.lista[i].marca += " " + aux;
      
    }

    return true;
}

bool LeerAlquileres(ListaAlquileres& listaA, ListaCoches& listaC)
{
    ifstream entrada("rent.txt");

    if (!entrada.is_open()) {
        cout << "ERROR";
        return false;
    }

    entrada >> listaA.numElementos;

    listaA.size = listaA.numElementos + 10;

    listaA.lista = new Alquiler[listaA.size];

    for (int i = 0; i < listaA.numElementos; i++)
    {
        int codigo;
        entrada >> codigo;

        int indiceCoche = BuscarCoche(codigo, listaC);

        if (indiceCoche == -1)
        {
            listaA.lista[i].coche = nullptr;
        }
        else
        {
            listaA.lista[i].coche = &listaC.lista[indiceCoche];
        }

        entrada >> listaA.lista[i].fecha;

        entrada >> listaA.lista[i].dias;


    }

    return true;
}

bool operator<(const Alquiler& izdo, const Alquiler& dcho) 
{
    return izdo.fecha < dcho.fecha;
}

void OrdenarAlquileres(ListaAlquileres& listaAlq) 
{
    sort(listaAlq.lista, listaAlq.lista + listaAlq.numElementos);
}



int main()
{
    SetConsoleOutputCP(CP_UTF8);

    ListaCoches listaC;
    ListaAlquileres listaA;

    LeerModelos(listaC);

    LeerAlquileres(listaA, listaC);

    OrdenarAlquileres(listaA);

    MostrarAlquileres(listaA);

    delete[] listaC.lista;
    delete[] listaA.lista;
}

