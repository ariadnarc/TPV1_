#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Ufo.h"



void Ufo::Save(std::ostream& out) const{

	out << 5 << " ";

	SceneObject::Save(out);

	out << state << " " << _currentFrame << " ";

	out << '\n';

}


