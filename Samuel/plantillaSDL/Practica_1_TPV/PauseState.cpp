#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "PauseState.h"
#include "Game.h"
#include "PlayState.h"



PauseState::PauseState(Game* game, PlayState* previusPlayState)
	:GameState(game),previusPlayState(previusPlayState),
	continueGameButton(new Button(this, game->getTexture(CONTINUAR), Point2D<>(315, 100))),
	saveGameButton(new Button(this, game->getTexture(GUARDAR_PARTIDA), Point2D<>(240, 200))),
	loadGameButton(new Button(this, game->getTexture(CARGAR_PARTIDA), Point2D<>(255, 300))),
	exitButton(new Button(this, game->getTexture(SALIR), Point2D<>(360, 400)))
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
	previusPlayState->SaveGame("partidas_guardadas/save1.txt");
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

void PauseState::Render() const {

	previusPlayState->Render();

	SDL_Rect aux{ 0, 0, winWidth, winHeight };

	SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(game->getRenderer(), 10, 10, 10, 100);

	SDL_RenderFillRect(game->getRenderer(), &aux);

	//SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_NONE);
	//SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);


	GameState::Render();
	

}