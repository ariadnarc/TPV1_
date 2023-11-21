#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Ufo.h"
#include "Game.h"


//constructor por parametros, sin terminar
Ufo::Ufo(Game* game, Point2D<> pos)
	:SceneObject(game, pos, 0, 0, 1) {};


//constructor por lectura de archivo
Ufo::Ufo(Game* game, std::istream& in)
	:SceneObject(game, in) {

	//leer estado y espera
	in >> state >> _currentFrame;
		
}



void Ufo::Save(std::ostream& out) const{

	out << UFO << " ";

	SceneObject::Save(out);

	out << state << " " << _currentFrame << " ";

	out << '\n';

}


