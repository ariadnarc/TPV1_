#include "SDL.h"
#include "InfoBar.h"
#include "checkML.h"
#include <iostream>


void InfoBar::Render() const{
	
	for (int i = 0; i < lifesLeft; i++) {
		SDL_Rect spaceshipRect;
		spaceshipRect.x = RectX + separacion * i; // ??? esto debe de hacer algo que los separe o algo no esta bien
		spaceshipRect.y = RectY;
		spaceshipRect.w = spaceshipText->getFrameWidth();
		spaceshipRect.h = spaceshipText->getFrameHeight();
		spaceshipText->render(spaceshipRect);
	}
}

void InfoBar::Lifes(int lifes) {
	lifesLeft = lifes;
}