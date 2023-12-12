#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "PauseState.h"
#include "Game.h"
#include "PlayState.h"


PauseState::PauseState(Game* game, PlayState* previusPlayState)
	:GameState(game),previusPlayState(previusPlayState),
	continueGameButton(new Button(this, game->getTexture(CONTINUAR), Point2D<>(365, 100))),
	saveGameButton(new Button(this, game->getTexture(GUARDAR_PARTIDA), Point2D<>(330, 200))),
	loadGameButton(new Button(this, game->getTexture(CARGAR_PARTIDA), Point2D<>(330, 300))),
	exitButton(new Button(this, game->getTexture(SALIR), Point2D<>(380, 400)))
{

	addObject(continueGameButton);
	addObject(saveGameButton);
	addObject(loadGameButton);
	addObject(exitButton);

	addEventListener(continueGameButton);
	addEventListener(saveGameButton);
	addEventListener(loadGameButton);
	addEventListener(exitButton);

	continueGameButton->connect([this]() {Continue(); });
	saveGameButton->connect([this]() {SaveGame(); });
	loadGameButton->connect([this]() {LoadGame(); });
	exitButton->connect([this]() {Exit(); });



}

void PauseState::Continue() {
	game->getGameStateMachine()->popState();
}
void PauseState::SaveGame() {

}
void PauseState::LoadGame() {
	//leer el numero de partida a cargar
	//...

	//cargar la partida en un nuevo estado
	game->getGameStateMachine()->popState();
	game->getGameStateMachine()->replaceState(new PlayState(game, "partidas_guardadas/save1.txt"));

}
void PauseState::Exit() {
	game->getGameStateMachine()->popState();
	game->getGameStateMachine()->popState();

}