#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "SceneObject.h"




void SceneObject::Save(std::ostream& out) {

	out << pos.getX() << " " << pos.getY() << " " << lifesLeft;
}