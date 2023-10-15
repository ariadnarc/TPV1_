#include<iostream>
#include<fstream>//para flujo de archivos, entrada/salida
#include "ListaAlquileres.h"
#include<algorithm>//para usar el sort

using namespace std;//en los cpp si se puede poner el using

//constructor pasando campos
ListaAlquileres::ListaAlquileres(Alquiler* _lista, int _size, int numElem)
    : lista(_lista), size(_size), numElementos(numElem) {};
//constructor por copia
ListaAlquileres::ListaAlquileres(const ListaAlquileres& listaA)
    : size(listaA.size), numElementos(listaA.numElementos)
{
    lista = new Alquiler[size];

    for (int i = 0; i < numElementos; i++) {
        lista[i] = listaA.lista[i];
    }
};


//sobrecarga del operador =, constructor por asignacion
ListaAlquileres& ListaAlquileres::operator=(const ListaAlquileres& listaA) {

    if (this == &listaA) return *this;

    //borrar memoria anterior
    this->~ListaAlquileres();
    
    size = listaA.size;
    numElementos = listaA.numElementos;

    lista = new Alquiler[size];

    for (int i = 0; i < numElementos; i++) {
        lista[i] = listaA.lista[i];
    }

    return *this;
}




void ListaAlquileres::MostrarAlquileres() const
{
    cout << *this;
}

//sobrecarga del operador de escritura
ostream& operator <<(ostream& out, const ListaAlquileres& listaA) {
    for (int i = 0; i < listaA.numElementos; i++) {
        out << listaA.lista[i];
    }
    return out;
}



bool ListaAlquileres::LeerAlquileres(const ListaCoches& listaC)
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
        //leer el codigo del coche alquilado
        int codigo;
        entrada >> codigo;

        AsignarIndiceCoche(codigo, listaC, lista[i]);

        lista[i].leerFechaYDias(entrada);                
    }
    return true;
}


void ListaAlquileres:: OrdenarAlquileres(){
    sort(lista, lista + numElementos);
}


void ListaAlquileres::AgregarAlquiler(Alquiler& alq) {
    
    if (numElementos == size) RedimensionarLista();

    Date fecha = alq.getFecha();

    //esto en vez de ser lineal podría ser logaritmico
    int i = 0;
    while (i < numElementos && lista[i].getFecha() < fecha)i++;


    int j = numElementos;

    //abrir hueco en el array
    while (j > i) {
        lista[j] = lista[j - 1];
        j--;
    }


    lista[i] = alq;
    numElementos++;
}






void ListaAlquileres::AsignarIndiceCoche(int codigo, const ListaCoches& listaC, Alquiler& alq) {
    //buscar el indice correspondiente al coche
    int indiceCoche = listaC.BuscarCoche(codigo);
   
    //asignar el puntero del coche
    alq.setCoche(indiceCoche == -1 ? nullptr : listaC.GetCoche(indiceCoche));
    

    /*
    Otra forma de hacerlo
    if (indiceCoche == -1) {
        alq.setCoche(nullptr);
    }
    else {
        alq.setCoche(listaC.GetCoche(indiceCoche));
    }
    */  
}

void ListaAlquileres::RedimensionarLista() {
    Alquiler* aux = new Alquiler[size * 2];

    for (int i = 0; i < numElementos; i++) {
        aux[i] = lista[i];
    }

    delete[] lista;

    lista = aux;
    size = size * 2;
}




//destructor 
ListaAlquileres::~ListaAlquileres() {
    delete[] lista;
}