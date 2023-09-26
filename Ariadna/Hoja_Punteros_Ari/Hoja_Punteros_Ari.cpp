#include <iostream>
#include <string>
using namespace std;

struct Registro {
    string nombre;
    double sueldo;
    int edad;
};

void func(Registro *reg, double *irpf, int *edad) {
    const double TIPO = 0.18;
    reg->edad++;
    *irpf = reg->sueldo * TIPO;
    *edad = reg->edad;
}

void funcC(const Registro *reg, double *irpf, int *edad) {
    const double TIPO = 0.18;
    // reg.edad++; // Error de compilaci�n
    *irpf = reg->sueldo * TIPO;
    *edad = reg->edad;
}


int main()
{
    Registro r1;
    Registro* pr = new Registro;

    // los registros r1 y *pr toman valor

    double cotiza; int a�os;

    func(&r1, &cotiza, &a�os);
    func(pr, &cotiza, &a�os);
    
}


