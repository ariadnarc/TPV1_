#include "checkML.h"


#include <iostream>
#include "SDL.h"
#include "Laser.h"
#include "Game.h"//para poder usar el game


void Laser::Render() const  {	
	SDL_Rect rect = getRect();

	SDL_SetRenderDrawColor(game->getRenderer(), color == 'r' ? 255 : 0, 0, color == 'r' ? 0 : 255, 255);
	SDL_RenderFillRect(game->getRenderer(), &rect);
}

void Laser::Move() {
	pos = pos + (velocityVector * velocity);
}

bool Laser::Colisions() {
	return game->collisions(this);;
}

void  Laser::Update() {

	if (lifesLeft <= 0) return;//para no hacer llamadas en un objeto muerto


	_currentFrame++;
	if (_currentFrame >= _frameRate) {
		Move();

		_currentFrame = 0;
	}

	if (Colisions() || pos.getY() < 0 || pos.getY() > winHeight) {
		game->HasDied(iterator);
	}
}

SDL_Rect Laser::getRect()const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = WIDTH;
	rect.h = HEIGHT;

	return rect;
}

bool Laser::Hit(SDL_Rect rect, char tLaser) {
	bool colision = false;

	SDL_Rect aux = getRect();


	if (tLaser != color) {
		if (SDL_HasIntersection(&rect, &aux)) {
			colision = true;
			lifesLeft--;
			if (lifesLeft <= 0) game->HasDied(iterator);
		}
	}

	return colision;
}



void Laser::Save(std::ostream& out) const {

}
