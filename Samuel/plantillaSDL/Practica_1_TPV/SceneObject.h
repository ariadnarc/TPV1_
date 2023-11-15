#ifndef SceneObject_H_
#define SceneObject_H_

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

	int lifesLeft;

	std::list<SceneObject*>::iterator iterator;

public:

	virtual	bool Hit(SDL_Rect rect, char tLaser) = 0;


	//constructor
	SceneObject(Game* game, Point2D<> _pos, int width, int height, int lifesLeft)
		: GameObject(game), pos(_pos), width(width), height(height), lifesLeft(lifesLeft){};

	//constructor por flujo

	//hace falta volver a poner el destructor?
	virtual ~SceneObject() {};

	void setListIterator(std::list<SceneObject*>::iterator it) { iterator = it; }

	virtual void Save(std::ostream& out) const;


};



#endif // !SceneObject_H_

