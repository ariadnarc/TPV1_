#include "checkML.h"
#include "SDL.h"
#include <iostream>
#include "Laser.h"
#include "Game.h"

void Laser::Render() {

	SDL_Rect aux = GetRect();

	SDL_SetRenderDrawColor(game->GetRenderer(), originAlien ? 255 : 0, 0, originAlien ? 0 : 255, 255);
	SDL_RenderFillRect(game->GetRenderer(), &aux);
}

bool Laser::Update() {

	Move();

	return alive && !game->Collision(*this);
}

void Laser::Move() {
	
	pos = pos + velocity * vel;
}

SDL_Rect Laser::GetRect(){

	SDL_Rect _myRect;

	_myRect.x = pos.getX();
	_myRect.y = pos.getY();
	_myRect.w = WIDTH;
	_myRect.h = HEIGHT;

	return _myRect;
}

void Laser::Hit() {

	alive = false;
}
