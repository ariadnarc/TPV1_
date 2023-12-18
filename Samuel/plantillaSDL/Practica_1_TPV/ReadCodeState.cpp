#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "ReadCodeState.h"
#include "Game.h"


ReadCodeState::ReadCodeState(Game* game, PauseState* previous)
	:GameState(game),previousPauseState(previous) {

}

void ReadCodeState::Render() const {

	previousPauseState->Render();

	SDL_Rect yellowBox{ 250,150,350,200 };
	SDL_Rect blackBox{ 253,153,344,194 };

	//color amarillo
	SDL_SetRenderDrawColor(game->getRenderer(), 255, 255, 0, 255);

	//render del borde amarrilo
	SDL_RenderFillRect(game->getRenderer(), &yellowBox);

	//color negro
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);

	//render del relleno negro
	SDL_RenderFillRect(game->getRenderer(), &blackBox);

	//resetear el color
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);


}
