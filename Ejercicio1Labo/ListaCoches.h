//
// Declaración de la clase ListaCoches
//

#include <iostream>
#include "Coche.h"

using namespace std;


#ifndef ListaCoches_H_
#define ListaCoches_H_

class ListaCoches
{
private:
    Coche** lista;
    int size, numElementos;

public:

    int BuscarCoche(int codigo);

    bool LeerModelos();

    Coche* GetCoche(int index);

    void LimpiarMemoria();
    
};

#endif // ListaCoches_H_