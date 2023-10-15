// Samuel García Bazán
// Ariadna Alicia Ruiz Castillo
// Grupo 15

#include <iostream>
#include <fstream>
#include <Windows.h>//para los caracteres de salida
#include "ListaAlquileres.h" //llamadas recursivas a los otros includes


#include "checkML.h"


using namespace std;


void RenderMenu() 
{
    cout << "\033[2J\033[1;1H";//clear de la pantalla
    cout << "1: Mostrar coches" << '\n';
    cout << "2: Mostrar Alquileres" << '\n';
    cout << "3: Añadir coche" << '\n';
    cout << "4: Añadir Alquiler" << '\n';
    cout << "5: Salir" << '\n';
}


void ProcesaInput(ListaCoches& listaC, ListaAlquileres& listaA,int accion) 
{
    if (accion == 1) {
        listaC.MostrarCoches();
    }
    else if (accion == 2) {
        listaA.MostrarAlquileres();
    }
    else if (accion == 3) {
        
        int codigo, precioDia;
        string marca;

        //Pedir datos
        cout << "Codigo:";
        cin >> codigo;
        cout << endl; 

        cout << "Precio Dia:";
        cin >> precioDia;
        cout << endl;
        
        cout << "Marca:";
        cin >> marca;
        cout << endl;

        //crear el coche
        Coche* aux = new Coche(codigo,precioDia,marca);
        
        //agregar el coche a la lista
        listaC.AgregarCoche(aux);
        
    }
    else if (accion == 4) {

        int codigoCoche;
        int dias;
        Date fecha;

        //pedir datos
        cout << "CodigoCoche:";
        cin >> codigoCoche;
        cout << endl;

        cout << "Fecha:";
        cin >> fecha;
        cout << endl;

        cout << "Dias:";
        cin >> dias;
        cout << endl;

        //rellenar el alquiler 
        //esto igual es mejor hacerlo de otra manera
        Alquiler aux(nullptr,fecha,dias);

        //asignar el indice del coche al alquiler
        listaA.AsignarIndiceCoche(codigoCoche, listaC, aux);
        
        //agregar el alquiler a la lista
        listaA.AgregarAlquiler(aux);
    }
    else {
        cout << "Por favor escriba un comando valido";
    }

    system("PAUSE");
}


int main()
{
    SetConsoleOutputCP(CP_UTF8);//para los caracteres de salida

    ListaAlquileres listaA;
    ListaCoches listaC;

    int accion = -1;

    listaC.LeerModelos();

    listaA.LeerAlquileres(listaC);

    listaA.OrdenarAlquileres();
    

    ListaAlquileres a(listaA);
    ListaCoches lista2(listaC);

    RenderMenu();

    cin >> accion;

    //bucle principal
    while (accion != 5) {
        ProcesaInput(listaC, listaA, accion);
        
        RenderMenu();

        cin >> accion;
    }


    //pruebas para comprobar que no hay fugas de memoria

    ListaAlquileres auxA(listaA);
    auxA = listaA;

    ListaCoches auxC(listaC);
    auxC = listaC;
}