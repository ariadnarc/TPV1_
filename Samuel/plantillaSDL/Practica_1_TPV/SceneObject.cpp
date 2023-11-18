#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "SceneObject.h"
#include "GameObject.h"



SceneObject::SceneObject(Game* game, std::istream& in) : GameObject(game) {

	int x, y;

	in >> x >> y;

	pos = Point2D<>(x, y);
}



void SceneObject::Save(std::ostream& out) const{

	out << pos.getX() << " " << pos.getY() << " ";
}