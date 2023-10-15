#ifndef ListaCoches_H_
#define ListaCoches_H_

//ponemos los include dentro del define
#include <iostream>
#include "Coche.h"

#include "checkML.h"



class ListaCoches
{
private:
    Coche** lista;
    int size, numElementos;

public:

    //constructores

    //constructor vacio
    ListaCoches(): lista(nullptr), size(-1),numElementos(-1){};
    //constructor pasando valores
    ListaCoches(Coche** _lista, int _size, int _numElementos);
    //constructor por copia
    ListaCoches(const ListaCoches& listaC);
    
    ListaCoches& operator=(const ListaCoches& listaC);


    //const, no modifica los datos
    int BuscarCoche(int codigo) const;

    void AgregarCoche(Coche*& c);
    
    
    bool LeerModelos();

    void MostrarCoches()const;

    //sobrecarga de los operadores de escritura y lectura
    friend std::ostream& operator<<(std::ostream& out, const ListaCoches& listaC);
    friend std::istream& operator>>(std::istream& in,ListaCoches& listaC);


    //getter del coche, devuelve el puntero al coche iesimo de la lista
    Coche* GetCoche(int index) const;
   
    //destructor
    ~ListaCoches();

private:
    void RedimensionarLista();

};

#endif // ListaCoches_H_