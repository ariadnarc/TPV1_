#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "PauseState.h"
#include "Game.h"
#include "PlayState.h"
#include "ReadCodeState.h"



PauseState::PauseState(Game* game, PlayState* previusPlayState)
	:GameState(game),previusPlayState(previusPlayState),
	continueGameButton(new Button(this, game->getTexture(CONTINUAR), Point2D<>(315, 100))),
	saveGameButton(new Button(this, game->getTexture(GUARDAR_PARTIDA), Point2D<>(240, 200))),
	loadGameButton(new Button(this, game->getTexture(CARGAR_PARTIDA), Point2D<>(255, 300))),
	exitButton(new Button(this, game->getTexture(SALIR), Point2D<>(360, 400)))
{
	//añadir botones a la lista de objetos
	addObject(continueGameButton);
	addObject(saveGameButton);
	addObject(loadGameButton);
	addObject(exitButton);

	//añadir botones a la lista de eventListener
	addEventListener(continueGameButton);
	addEventListener(saveGameButton);
	addEventListener(loadGameButton);
	addEventListener(exitButton);

	//conectar cada funcion con su callback
	continueGameButton->connect([this]() {Continue(); });
	saveGameButton->connect([this]() {SaveGame(); });
	loadGameButton->connect([this]() {LoadGame(); });
	exitButton->connect([this]() {Exit(); });



}

void PauseState::Continue() {
	game->getGameStateMachine()->popState();
}
void PauseState::SaveGame() {
	saving = true;
	game->getGameStateMachine()->pushState(new ReadCodeState(game, this));
}
void PauseState::LoadGame() {
	loading = true;
	game->getGameStateMachine()->pushState(new ReadCodeState(game, this));
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

	SDL_SetRenderDrawBlendMode(game->getRenderer(), SDL_BLENDMODE_NONE);
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);


	GameState::Render();
	

}

void PauseState::ReturnFromReadCode(std::string codeNumber) {
	if (saving) {
		saving = false;
		previusPlayState->SaveGame("partidas_guardadas/save" + codeNumber + ".txt");
	}
	else if (loading) {
		loading = false;
		//cargar la partida en un nuevo estado

		try {
			PlayState* aux = new PlayState(game, "partidas_guardadas/save" + codeNumber + ".txt");
			game->getGameStateMachine()->popState();
			game->getGameStateMachine()->replaceState(aux);
		}
		catch (FileNotFoundError error) {
			SDL_ShowSimpleMessageBox(0, "Untitled", error.what(), nullptr);

		}
	}
}