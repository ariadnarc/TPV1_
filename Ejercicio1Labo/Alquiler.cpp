#include"Alquiler.h"
#include <fstream>


using namespace std;//en los cpp se puede poner el using


//constructor pasando campos
Alquiler::Alquiler(Coche* pCoche,Date date,int nDias) 
    : coche(pCoche),fecha(date),dias(nDias) {}
//constructor por copia
Alquiler::Alquiler(const Alquiler& a) 
    :coche(a.coche), fecha(a.fecha),dias(a.dias) {}


//sobrecarga del operador < , comparador
bool Alquiler:: operator<(const Alquiler& dcho) {
	return fecha < dcho.fecha;
}

//sobrecarga del operador de escritura
ostream& operator<<(ostream& out, const Alquiler& alq) {
    
    if (alq.coche == nullptr){
        cout << alq.fecha << " " << "ERROR: modelo inexistente." << std::endl;
    }
    else{
        cout << alq.fecha << " " << alq.coche->getMarca() << " " << alq.dias << " día(s) por "
            << alq.dias * alq.coche->getPrecioDia() << " euros." << std::endl;
    }

    return out;
}

//setters
void Alquiler::setCoche(Coche* c) {
    coche = c;
}
void Alquiler::setFecha(const Date& d) {
    fecha = d;
}
void Alquiler::setDias(int d) {
    dias = d;
}


//getters
Date Alquiler::getFecha()const {
    return fecha;
}


void Alquiler::leerFechaYDias(istream& entrada){
    entrada >> fecha >> dias;   
}

