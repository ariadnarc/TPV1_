#include<iostream>
#include"Alquiler.h"


bool Alquiler:: operator<(const Alquiler& dcho) {
	return fecha < dcho.fecha;
}