#pragma once

#include "SDL.h"
#include "checkML.h"
#include "GameObject.h"
#include <iostream>
#include "Vector2D.h"

class MotherShip : public GameObject {

	Vector2D<> Aliensdir;

	bool cannotMove = false;

	bool shouldmove = false;


};