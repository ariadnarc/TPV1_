#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include <string>


#include "InfoBar.h"
#include "Game.h"


void InfoBar::RenderLifes() const {
	SDL_Rect target;

	target.w = cannonTexture->getFrameWidth();
	target.h = cannonTexture->getFrameHeight();

	for (int i = 0; i < currentLifes; i++) {

		target.x = lifesStartX + lifesSeparationX * (i % lifesPerRow);
		target.y = lifesStartY + lifesSeparationY * (i / lifesPerRow);

		cannonTexture->render(target);
	}
}

void InfoBar::RenderScore()const {

	//render del texto score
	SDL_Rect scoreTarget{ scoreStartX,scoreStartY,scoreTexture->getFrameWidth(),scoreTexture->getFrameHeight() };

	scoreTexture->render(scoreTarget);

	//render del numero de la puntuacion actual
	SDL_Rect numberTarget{ scoreStartX + 150,scoreStartY,numberTexture->getFrameWidth(),numberTexture->getFrameHeight()};

	numberTexture->render(numberTarget);

}

void InfoBar::Render()const {
	RenderLifes();

	RenderScore();
}

void InfoBar::UpdateCurrentLifes(int lifes) {
	currentLifes = lifes;
}

void InfoBar::UpdateCurrentScore(int score) {
	delete numberTexture;
	numberTexture = font->generateTexture(game->getRenderer(), std::to_string(currentScore), SDL_Color{ 255,255,255,255 });
	currentScore = score;
}