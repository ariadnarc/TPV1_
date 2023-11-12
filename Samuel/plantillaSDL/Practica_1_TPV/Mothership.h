#ifndef Mothership_H_
#define Mothership_H_


#include <iostream>
#include <SDL.h>

#include "GameObject.h"
#include "Vector2D.h"

#include "checkML.h"


class MotherShip : public GameObject {

	Vector2D<> aliensDir;

	bool cannotMove = false;

	//a lo mejor no hace falta
	//bool goDown = false;

	//enumerado state ...

	//level de descenso ...



public://metodos, puede que esten mal los tipos o que haya que añadir parametros

	Vector2D<> getDirection() const { return aliensDir; };

	bool shouldMove();

	void cannotMove();

	void alienDied();

	void alienLanded();

	void haveLanded();

	int getAlienCount();


};




#endif // !Mothership_H_

