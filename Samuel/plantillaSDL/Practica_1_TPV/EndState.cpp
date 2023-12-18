#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "EndState.h"
#include "Game.h"

EndState::EndState(Game* game,bool win)
	:GameState(game), win(win),

	returnToMenuButton(new Button(this, game->getTexture(CONTINUAR), Point2D<>(305, 250))),
	exitButton(new Button(this, game->getTexture(SALIR), Point2D<>(355, 400)))
{
	//añadir a la lista de objetos
	addObject(returnToMenuButton);
	addObject(exitButton);

	//añadir a la lista de eventHandler
	addEventListener(returnToMenuButton);
	addEventListener(exitButton);

	//asignar callbacks
	returnToMenuButton->connect([this]() {ReturnToMenu(); });
	exitButton->connect([this]() {Exit(); });
}


void EndState::Render()const {

	game->RenderClear();

	GameState::Render();

	//renderizar texto segun hemos ganado o perdido
	SDL_Rect aux{ win ? 295 :315,100,
		game->getTexture(win ? HAS_GANADO : GAMEOVER)->getFrameWidth(),
		game->getTexture(win ? HAS_GANADO : GAMEOVER)->getFrameHeight() };

	//render del mensaje de gameOver o has ganado
	game->getTexture(win ? HAS_GANADO : GAMEOVER)->render(aux);
}

void EndState::ReturnToMenu() {
	game->getGameStateMachine()->popState();
}

void EndState::Exit() {
	game->getGameStateMachine()->popState();
	game->getGameStateMachine()->popState();
}