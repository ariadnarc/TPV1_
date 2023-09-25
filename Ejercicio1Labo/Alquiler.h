//
// Declaración del struct Alquiler
//

#include <iostream>
#include "Coche.h"
#include "Date.h"

#ifndef Alquiler_H_
#define Alquiler_H_

struct Alquiler
{
    Coche* coche;
    Date fecha;
    int dias;

    bool operator<(const Alquiler& dcho);
};

#endif