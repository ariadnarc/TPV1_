#ifndef Coche_H_
#define Coche_H_

//metemos los include dentro del define
#include<iostream>
#include "checkML.h"


class Coche
{
private:
    int codigo, precioDia;
    std::string marca;
public:

    //constructores

    //constructor vacio
    Coche() : codigo(-1), precioDia(-1),marca("") {};
    //constructor pasando los campos
    Coche(int cod,int precio,std::string nombreMarca);
    //constructor por copia
    Coche(const Coche& c);


    //getters (const, no modifican los datos)
    int getCodigo()const;
    int getPrecioDia()const;
    std::string getMarca()const;


    //setters
    void setCodigo(int c);
    void setPrecioDia(int p);
    void setMarca(std::string m);

    //la declaramos como friend de esta funcion para poder acceder a los campos privados
    //sobrecargar el operador de lectura
    friend std::istream& operator>>(std::istream& in, Coche& c);

    //sobrecargar el operador de escritura
    friend std::ostream& operator<<(std::ostream& out, const Coche& c);
};

#endif
