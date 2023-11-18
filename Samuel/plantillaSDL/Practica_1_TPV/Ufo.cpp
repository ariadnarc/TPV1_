#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Ufo.h"
#include "Game.h"




void Ufo::Save(std::ostream& out) const{

	out << UFO << " ";

	SceneObject::Save(out);

	out << state << " " << _currentFrame << " ";

	out << '\n';

}


