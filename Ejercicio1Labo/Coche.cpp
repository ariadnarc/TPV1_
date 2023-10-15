#include "Coche.h"
#include <string> //para poder usar el getline

using namespace std;//lo ponemos en los cpp pero no en las cabeceras

//constructor pasando los campos
Coche::Coche(int cod, int precio, string nombreMarca)
	: codigo(cod),precioDia(precio),marca(nombreMarca) {}
//constructor por copia
Coche::Coche(const Coche& c) 
	:codigo(c.codigo),precioDia(c.precioDia),marca(c.marca) {}



//operador de lectura
istream& operator>>(std::istream& in, Coche& c) {
	in >> c.codigo >> c.precioDia;//podemos acceder a los valores porque hemos usado el friend
	getline(in, c.marca);
	return in;
}


//operador de escritura
ostream& operator<<(ostream& out, const Coche& c){
	out << c.codigo << " " << c.precioDia << " " << c.marca;
	return out;
}

//getters (son const, no modifican los datos, importante ponerlo)

int Coche::getCodigo()const {
	return codigo;
}
int Coche::getPrecioDia()const {
	return precioDia;
}
string Coche::getMarca()const {
	return marca;
}


//setters

void Coche::setCodigo(int c) {
	codigo = c;
}

void Coche::setPrecioDia(int p) {
	precioDia = p;
}

void Coche::setMarca(string m) {
	marca = m;
}
