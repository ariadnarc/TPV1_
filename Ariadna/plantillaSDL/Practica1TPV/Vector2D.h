#pragma once
#include "checkML.h"
#include "SDL.h"
#include <iostream>

//tenemos que preguntar que esto solo vale para int y para double
template<class T = double>
class Vector2D {

	T x,y; 

public:

	//constructores
	Vector2D() { x = 0; y = 0; }
	Vector2D(T _x, T _y) : x(_x), y(_y) {};

	T getX()const { return x; }
	T getY()const { return y; }

	//suma
	Vector2D operator+(const Vector2D& other) {
		return Vector2D(x + other.x, y + other.y);
	}
	
	//resta
	Vector2D operator-(const Vector2D& other) {
		return Vector2D(x - other.x, y - other.y);
	}
	
	//producto escalar
	T operator*(const Vector2D& other) {
		return (x * other.x) + (y * other.y);
	}

	//multiplicacion vector por escalar
	Vector2D operator*(double escalar) {
		return Vector2D(x * escalar, y * escalar);
	}
};

template<class T = double>
using Point2D = Vector2D<>;
