#include "checkML.h"
#include "SDL.h"
#include <iostream>
#include "Bunker.h"

void Bunker::Render()const {
	texture->renderFrame(GetRect(), 0, texture->getNumColumns() - lifesLeft);
}

/*  mal porque ahora esto es un void
bool Bunker::Update() {
	return lifesLeft > 0;
}
*/

void Bunker::Hit() {
	lifesLeft--;
}

SDL_Rect Bunker::GetRect() const{
	SDL_Rect target;

	target.x = pos.getX();
	target.y = pos.getY();
	target.w = texture->getFrameWidth();
	target.h = texture->getFrameHeight();

	return target;
}