#include <iostream>
#include <SDL.h>
#include "Bunker.h"
#include "Game.h"

#include "checkML.h"


void Bunker::Render() const{
	int cols = texture->getNumColumns();
	int indiceFrame = cols - std::ceil((double)lifesLeft / (BUNKER_LIFES / cols));

	texture->renderFrame(getRect(), 0,std::clamp(indiceFrame,0,cols));
}

bool Bunker::Update() {
	return lifesLeft > 0;
}

void Bunker::Hit() {
	lifesLeft--;
}

SDL_Rect Bunker::getRect()const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	return rect;
}

