#include <iostream>
#include <SDL.h>

#include "InfoBar.h"

#include "checkML.h"


void InfoBar::RenderLifes() {
	SDL_Rect target;

	target.w = cannonTexture->getFrameWidth();
	target.h = cannonTexture->getFrameHeight();

	for (int i = 0; i < currentLifes; i++) {

		target.x = lifesStartX + lifesSeparationX * (i % lifesPerRow);
		target.y = lifesStartY + lifesSeparationY * (i / lifesPerRow);

		cannonTexture->render(target);
	}
}

void InfoBar::RenderScore() {

	std::vector<int> rows = {1,1,1,1,1};
	std::vector<int> cols = {'S'-'A','C' - 'A' ,'O' - 'A' ,'R' - 'A' ,'E' - 'A' };//cambiar a una funcion

	SDL_Rect target;

	target.y = scoreStartY;

	target.w = fontTexture->getFrameWidth();
	target.h = fontTexture->getFrameHeight();

	int i;
	//render del SCORE
	for (i = 0; i < 5; i++) {
		target.x = scoreStartX + fontTexture->getFrameWidth()*i;

		fontTexture->renderFrame(target, rows[i], cols[i]);
	}
	//render de :
	target.x = scoreStartX + fontTexture->getFrameWidth() * i;
	fontTexture->renderFrame(target, 2, 11);


	int aux = currentScore;

	target.x = scoreEndX;
	//render de la puntuacion
	while (aux >= 10) 
	{
		fontTexture->renderFrame(target, 2, aux%10);
		target.x -= fontTexture->getFrameWidth();
		aux /= 10;
	}
	fontTexture->renderFrame(target, 2, aux % 10);


}


void InfoBar::Render() {
	RenderLifes();

	RenderScore();
}

void InfoBar::UpdateCurrentLifes(int lifes) {
	currentLifes = lifes;
}

void InfoBar::UpdateCurrentScore(int score) {
	currentScore = score;
}