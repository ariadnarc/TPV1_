#include <iostream>
#include "SDL.h"
#include "Laser.h"
#include "Game.h"//para poder usar el game

#include "checkML.h"

void Laser::Render() {	
	SDL_Rect rect = getRect();

	SDL_SetRenderDrawColor(game->getRenderer(), originAlien ? 255:0,0,originAlien ? 0:255,255);
	SDL_RenderFillRect(game->getRenderer(), &rect);
}

void Laser::Move() {
	pos = pos + (velocityVector * velocity);
}

bool Laser::Colisions() {
	return game->collisions(this);;
}

bool Laser::Update() {

	_currentFrame++;
	if (_currentFrame >= _frameRate) {
		Move();

		_currentFrame = 0;
	}

	return !hited && !Colisions() && pos.getY() > 0;
}

SDL_Rect Laser::getRect()const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = WIDTH;
	rect.h = HEIGHT;

	return rect;
}

void Laser::Hit() {
	hited = true;
}
