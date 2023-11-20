#pragma once

#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include <list>

#include "GameObject.h"
#include "Vector2D.h"

class SceneObject : public GameObject {
protected:

	Point2D<> pos;

	int width;
	int height;



public:

	virtual bool Hit();

};
