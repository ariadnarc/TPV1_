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
	addObject(returnToMenuButton);
	addObject(exitButton);

	addEventListener(returnToMenuButton);
	addEventListener(exitButton);

	returnToMenuButton->connect([this]() {ReturnToMenu(); });
	exitButton->connect([this]() {Exit(); });


}


void EndState::Render()const {

	game->RenderClear();

	GameState::Render();

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