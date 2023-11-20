#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include "Bunker.h"
#include "Game.h"


/*
renderiza el bunker
si el bunker tiene un numero de vidas multiplo de 4, cada frame tiene las mismas vidas
si no, todos los frames tienen las vidas que tendrian con el multiplo de 4 anterior excepto el primero que tiene tambien el resto de vidas
ejemplo 
4 vidas 1 1 1 1
8 vidas 2 2 2 2
9 vidas 3 2 2 2 
10 vidas 4 2 2 2
11 vidas 5 2 2 2 
12 vidas 3 3 3 3


*/
void Bunker::Render() const{

	/* Version explicando el calculo
	//numero de columnas de la imagen, los frames que tiene el bunker
	int cols = texture->getNumColumns();

	//vidas minimas que tiene cada frame del bunker(division entera), 
	//el resto de vidas iran para el primer frame
	int lifesPerFrame = BUNKER_LIFES / cols;
	
	//como el indice esta invertido (el cuarto bunker es el que tiene menos vida), restamos a cols 
	//la division está con redondeada hacia arriba(ceil) para aproximar al frame correcto
	int indiceFrame = cols - std::ceil((double)lifesLeft / (lifesPerFrame));

	//clampeamos entre 0 y cols, los valores validos del frame
	int columaRender = std::clamp(indiceFrame, 0, cols);

	texture->renderFrame(getRect(), 0,columaRender);

	*/

	//version igual pero menos entendible
	int cols = texture->getNumColumns();

	int indiceFrame = cols - std::ceil((double)lifesLeft / (BUNKER_LIFES / cols));

	texture->renderFrame(getRect(), 0,std::clamp(indiceFrame,0,cols));
}

void Bunker::Update() {

}

bool Bunker::Hit(SDL_Rect rect, char tLaser) {

	if (lifesLeft <= 0) return false;

	bool colision = false;
	
	SDL_Rect aux = getRect();


	if (SDL_HasIntersection(&rect, &aux)) {
		colision = true;
		lifesLeft--;
		if (lifesLeft <= 0) {
			game->HasDied(iterator);
		}
	}

	return colision;
}

SDL_Rect Bunker::getRect()const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	return rect;
}

//constructor por parametros
Bunker::Bunker(Game* game, Texture* text, Point2D<> _pos, int lifes)
	:SceneObject(game, _pos, 0, 0, lifes), texture(text) {};

//constructor por lectura de archivo
Bunker::Bunker(Game* game, Texture* text, std::istream& in) 
	: SceneObject(game,in),texture(text) {

	in >> lifesLeft;
}


void Bunker::Save(std::ostream& out) const {
	out << BUNKER << " ";

	SceneObject::Save(out);

	out << lifesLeft;

	out << '\n';


}
