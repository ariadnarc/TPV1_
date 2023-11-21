#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "SceneObject.h"
#include "GameObject.h"


//constructor por parametros
SceneObject::SceneObject(Game* game, Point2D<> _pos, int width, int height, int lifesLeft)
	: GameObject(game), pos(_pos), width(width), height(height), lifesLeft(lifesLeft) {};

//constructor por lectura de archivo
SceneObject::SceneObject(Game* game, std::istream& in) : GameObject(game) {

	int x, y;
	in >> x >> y;

	pos = Point2D<>(x, y);
}


void SceneObject::Save(std::ostream& out) const{

	out << pos.getX() << " " << pos.getY() << " ";
}


SDL_Rect SceneObject::getRect() const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = width;
	rect.h = height;

	return rect;
}

