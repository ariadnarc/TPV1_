#include "checkML.h"

#include <iostream>
#include <SDL.h>
#include <string>

#include "ReadCodeState.h"
#include "Game.h"



ReadCodeState::ReadCodeState(Game* game, PauseState* previous)
	:GameState(game),previousPauseState(previous) {
	font = game->getFont();

	textoCodigoTexture = game->getTexture(CODIGO);
}

ReadCodeState::ReadCodeState(Game* game, MainMenuState* previous)
	:GameState(game), previousMainMenuState(previous) {
	font = game->getFont();

	textoCodigoTexture = game->getTexture(CODIGO);
}

void ReadCodeState::Render() const {

	if (previousPauseState != nullptr) previousPauseState->Render();
	else previousMainMenuState->Render();

	SDL_Rect yellowBox{ 250,150,350,160 };
	SDL_Rect blackBox{ 253,153,344,154 };
	SDL_Rect textoCodigoBox{ 330,165,textoCodigoTexture->getFrameWidth(),textoCodigoTexture->getFrameHeight() };

	//color amarillo
	SDL_SetRenderDrawColor(game->getRenderer(), 255, 255, 0, 255);

	//render del borde amarrilo
	SDL_RenderFillRect(game->getRenderer(), &yellowBox);

	//color negro
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);

	//render del relleno negro
	SDL_RenderFillRect(game->getRenderer(), &blackBox);

	textoCodigoTexture->render(textoCodigoBox);

	if (codeTexture != nullptr) {
		SDL_Rect codeTarget{ 370,220,codeTexture->getFrameWidth(),codeTexture->getFrameHeight() };
		codeTexture->render(codeTarget);

	}

	//resetear el color
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);


}

void ReadCodeState::HandleEvent(const SDL_Event& ev) {
	SDL_Scancode code = ev.key.keysym.scancode;

	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code >= 30 && code <= 38 && nDigits <4 ) {

			int slotNumber = code - 29;
			
			codeNumber *= 10;
			codeNumber += slotNumber;
			nDigits++;

			delete codeTexture;
			codeTexture = font->generateTexture(game->getRenderer(), std::to_string(codeNumber), SDL_Color{ 255,255,0,255 });
		}
		else if (code == SDL_SCANCODE_BACKSPACE) {
			codeNumber /=  10;
			nDigits--;
			if (nDigits < 0)nDigits = 0;

			delete codeTexture;
			codeTexture = font->generateTexture(game->getRenderer(), std::to_string(codeNumber), SDL_Color{ 255,255,0,255 });

		}
		else if (code == SDL_SCANCODE_RETURN) {
			//volver al estado de pausa 
			game->getGameStateMachine()->popState();

			if (previousPauseState != nullptr) {
				previousPauseState->ReturnFromReadCode(std::to_string(codeNumber));
			}
			else {
				previousMainMenuState->ReturnFromReadCode(std::to_string(codeNumber));
			}
		}
		


		
	}
}

ReadCodeState::~ReadCodeState() {
	delete codeTexture;
}