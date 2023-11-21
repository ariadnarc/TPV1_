#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Ufo.h"
#include "Game.h"


//constructor por parametros, sin terminar
Ufo::Ufo(Game* game, Point2D<> pos)
	:SceneObject(game, pos, 0, 0, 1) {};


//constructor por lectura de archivo
Ufo::Ufo(Game* game,Texture* texture, std::istream& in)
	:SceneObject(game, in),texture(texture) {

	//leer estado y espera
	in >> state >> waitingFrames;
		
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}



void Ufo::Save(std::ostream& out) const{

	out << UFO_TYPE << " ";

	SceneObject::Save(out);

	out << state << " " << waitingFrames << " ";

	out << '\n';

}


