#include<iostream>
#include "ListaCoches.h"
#include <fstream> //para flujo de archivos, leer archivos de texto


using namespace std; //en los cpp si se puede poner el using std

//constructor pasando valores
ListaCoches::ListaCoches(Coche** _lista, int _size, int _numElementos)
    :lista(_lista), size(_size), numElementos(_numElementos) {};

//constructor por copia
ListaCoches::ListaCoches(const ListaCoches& listaC)
    :size(listaC.size), numElementos(listaC.numElementos) 
{
    //creamos una lista de punteros del mismo tamaño
    lista = new Coche * [size];
      
    //hasta numElementos, creamos un coche(por el constructor por copia) igual al coche de la lista original
    for (int i = 0; i < numElementos; i++) {
        lista[i] = new Coche(*listaC.lista[i]);
    }
    
    //desde numElementos hasta size, simplemente creamos un coche vacio
    for (int i = numElementos; i < size; i++) {
        lista[i] = new Coche();
    }   
};


ListaCoches& ListaCoches::operator=(const ListaCoches& listaC) {

    if (this == &listaC) return *this;

    //borrar memoria anterior
    this->~ListaCoches();

    size = listaC.size;
    numElementos = listaC.numElementos;

    //creamos una lista de punteros del mismo tamaño
    lista = new Coche * [size];

    //hasta numElementos, creamos un coche(por el constructor por copia) igual al coche de la lista original
    for (int i = 0; i < numElementos; i++) {
        lista[i] = new Coche(*listaC.lista[i]);
    }

    //desde numElementos hasta size, simplemente creamos un coche vacio
    for (int i = numElementos; i < size; i++) {
        lista[i] = new Coche();
    }

    return *this;
}

//implementacion con busqueda binaria(la lista de coches está ordenada)
int ListaCoches::BuscarCoche(int codigo)const {
    
    int cotaInferior = 0, cotaSuperior = numElementos, valorMedio = cotaSuperior / 2, resultado = -1;
    bool encontrado = false;
    while (!encontrado && cotaInferior <= cotaSuperior && valorMedio >= 0 && valorMedio < numElementos)
    {
        if (codigo == lista[valorMedio]->getCodigo())
        {
            resultado = valorMedio;
            encontrado = true;
        }
        else
        {
            if (codigo > lista[valorMedio]->getCodigo())
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

void ListaCoches::AgregarCoche(Coche*& c) {

    if (numElementos == size) RedimensionarLista();

    int codigo = c->getCodigo();

    //esto en vez de lineal se podria hacer logaritmico
    int i = 0;
    while (i < numElementos && codigo > lista[i]->getCodigo())i++;


    int j = numElementos;
        
    //abrir hueco en el array
    while (j > i) {
        lista[j] = lista[j - 1];
        j--;
    }
    
    lista[i] = c;

    numElementos++;
}


void ListaCoches::MostrarCoches()const {
    cout << *this;
}

bool ListaCoches::LeerModelos()
{
    ifstream entrada("coches.txt");

    if (!entrada.is_open()) {
        cout << "ERROR";
        return false;
    }

    entrada >> *this;

    return true;
}


//operador de escritura
ostream& operator<<(ostream& out, const ListaCoches& listaC){
    for (int i = 0; i < listaC.numElementos; i++) {
        out << *listaC.lista[i] << '\n';
    }
    return out;
}

//operador de lectura
istream& operator>>(istream& in, ListaCoches& listaC) {

    in >> listaC.numElementos;

    listaC.size = listaC.numElementos + 10;

    listaC.lista = new Coche * [listaC.size];

    //inicializar los punteros
    for (int i = 0; i < listaC.size; i++) {
        listaC.lista[i] = new Coche();
    }

    //leer coches
    for (int i = 0; i < listaC.numElementos; i++) {
        in >> *listaC.lista[i];
    }
    
    return in;
}


//getter
Coche* ListaCoches::GetCoche(int index)const {
    return lista[index];
}


void ListaCoches::RedimensionarLista() {

    Coche** aux = new Coche * [size * 2];

    for (int i = 0; i < numElementos; i++) {
        aux[i] = lista[i];
    }
    delete[] lista;

    lista = aux;
    size = size * 2;
}


//destructor
ListaCoches::~ListaCoches() {
    //borrar todos los elementos de la lista
    for (int i = 0; i < size; i++) {
        delete lista[i];
    }
    //borrar la lista
    delete[] lista;
}