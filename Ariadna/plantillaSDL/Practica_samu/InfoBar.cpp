#include <iostream>
#include <SDL.h>

#include "InfoBar.h"

#include "checkML.h"



void InfoBar::Render() {

	for (int i = 0; i < currentLifes; i++) {
		SDL_Rect target;

		target.x = startX + lifesSeparationX * (i%lifesPerRow);
		target.y = startY + lifesSeparationY * (i/lifesPerRow);

		target.w = cannonTexture->getFrameWidth();
		target.h = cannonTexture->getFrameHeight();


		cannonTexture->render(target);
	}
}

void InfoBar::UpdateCurrentLifes(int lifes) {
	currentLifes = lifes;
}