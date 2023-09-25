//
// Declaración e  implementacion de la clase ListaAlquileres
//

#include <iostream>
#include "Alquiler.h"
#include "ListaCoches.h"

#ifndef ListaAlquileres_H_
#define ListaAlquileres_H_

class ListaAlquileres
{
private:
    Alquiler* lista;
    int size, numElementos;
public:

    void MostrarAlquileres();

    bool LeerAlquileres(ListaCoches& listaC);
   
    void OrdenarAlquileres();

    void LimpiarMemoria();
};

#endif