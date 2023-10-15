#ifndef ListaAlquileres_H_
#define ListaAlquileres_H_

//los include dentro del define
#include <iostream>
#include "Alquiler.h"
#include "ListaCoches.h"

#include "checkML.h"



class ListaAlquileres
{
private:
    Alquiler* lista;
    int size, numElementos;
public:
    
    //constructores

    //contructor vacio
    ListaAlquileres() : lista(nullptr),size(-1),numElementos(-1){};
    //constructor pasando campos
    ListaAlquileres(Alquiler* _lista, int _size, int numElem);
    //constructor por copia
    ListaAlquileres(const ListaAlquileres& listaA);

    //sobrecarga del operador =, constructor por asignacion
    ListaAlquileres& operator =(const ListaAlquileres& listaA);

    //const, no modifica los datos
    void MostrarAlquileres()const;

    bool LeerAlquileres(const ListaCoches& listaC);
   
    void OrdenarAlquileres();

    void AgregarAlquiler(Alquiler& alq);


    //sobrecarga del opereador de escritura
    friend std::ostream& operator <<(std::ostream& out,const ListaAlquileres& listaA );

    //destructor
    ~ListaAlquileres();


    void AsignarIndiceCoche(int codigo, const ListaCoches& listaC, Alquiler& alq);
private:

    void RedimensionarLista();
};

#endif