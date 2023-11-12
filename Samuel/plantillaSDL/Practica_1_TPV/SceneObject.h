#ifndef SceneObject_H_
#define SceneObject_H_

#include <iostream>
#include <SDL.h>
#include <list>

#include "GameObject.h"
#include "Vector2D.h"

#include "checkML.h"



class SceneObject : public GameObject {

protected:

	Point2D<> pos;

	int width;
	int height;

	int lifesLeft;

	std::list<SceneObject*>::iterator iterator;

public:

	virtual	bool Hit(SDL_Rect rect, char tLaser) = 0;


	//constructor, hace falta?
	SceneObject(Game* game, Point2D<> _pos, int width, int height, int lifesLeft)
		: GameObject(game), pos(_pos), width(width), height(height), lifesLeft(lifesLeft){};

	//hace falta volver a poner el destructor?
	virtual ~SceneObject() {};

	void setListIterator(std::list<SceneObject*>::iterator it) { iterator = it; }

};



#endif // !SceneObject_H_

