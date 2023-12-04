#ifndef SceneObject_H_
#define SceneObject_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include <list>

#include "GameObject.h"
#include "Vector2D.h"
#include "InvadersError.h"


class SceneObject : public GameObject {

protected:

	Point2D<> pos;

	int width;
	int height;

	int lifesLeft = 1;

	std::list<SceneObject*>::iterator iterator;

public:

	virtual	bool Hit(SDL_Rect rect, char tLaser) = 0;


	//constructor por parametros
	SceneObject(PlayState* game, Point2D<> _pos, int width, int height, int lifesLeft);

	//constructor por lectura de archivo
	SceneObject(PlayState* game,std::istream& in);


	//hace falta volver a poner el destructor?
	virtual ~SceneObject() {};

	void setListIterator(std::list<SceneObject*>::iterator it) { iterator = it; }

	virtual void Save(std::ostream& out) const;

	SDL_Rect getRect()const;

protected:

	template<typename T>
	void readValue(T& v, std::istream& in) {
		in >> v;
		if (in.fail()) {
			throw FileFormatError("",0);
		}
	}

};

#endif // !SceneObject_H_