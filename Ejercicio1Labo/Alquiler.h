#ifndef Alquiler_H_
#define Alquiler_H_

//ponemos los include dentro del define
#include <iostream>
#include "Coche.h"
#include "Date.h"
#include <fstream>

#include "checkML.h"


class Alquiler
{
private:
    Coche* coche;
    Date fecha;
    int dias;
public:

    //constructores

    //constructor vacio
    Alquiler() : coche(nullptr), fecha(), dias(-1) {};
    //constructor pasando los campos
    Alquiler(Coche* pCoche,Date date, int nDias);
    //constructor por copia
    Alquiler(const Alquiler& a);

    //sobrecarga del operador <, para comparar los alquileres
    bool operator<(const Alquiler& dcho);

    //la declaramos como friend de esta funcion para poder acceder a los campos privados
    //sobrecargar el operador de escritura
    friend std::ostream& operator<<(std::ostream& out, const Alquiler& alq);

    //setters
    void setCoche(Coche* c);
    void setFecha(const Date& d);
    void setDias(int d);

    //getters

    Date getFecha()const;

    //funcion para inicializar la variable leyendo de un archivo de texto
    void leerFechaYDias(std::istream& entrada);
};


#endif