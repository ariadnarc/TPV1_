#include <iostream>
#include <string>
using namespace std;

struct Registro {
    string nombre;
    double sueldo;
    int edad;
};

void func(Registro* reg, double* irpf, int* edad) {
    const double TIPO = 0.18;
    reg->edad++;
    *irpf = reg->sueldo * TIPO;
    *edad = reg->edad;
}

void crearNuevoReg(Registro *&preg) {
    preg = new Registro; 
    // el registro *preg toma valor
}

int main()
{
    Registro r1 ;
    Registro* pr = nullptr;
    
    //crearNuevoReg(&r1); 
    crearNuevoReg(pr); // los registros r1 y *pr toman valor

    double cotiza; int años;

    func(&r1, &cotiza, &años);
    func(pr, &cotiza, &años);
}
