#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "MainMenuState.h"
#include "ReadCodeState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* game) 
	: GameState(game), 
	newGameButton(new Button(this, game->getTexture(NUEVA_PARTIDA), Point2D<>(245, 150))), 
	loadGameButton(new Button(this, game->getTexture(CARGAR_PARTIDA), Point2D<>(232,200))),
	exitButton(new Button(this, game->getTexture(SALIR), Point2D<>(345, 250)))
{
	//añadir los objetos a la lista de GameObjects, para el renderizado
	addObject(newGameButton);
	addObject(loadGameButton);
	addObject(exitButton);

	//añadir los objetos a la lista de escuchantes de eventos
	addEventListener(newGameButton);
	addEventListener(loadGameButton);
	addEventListener(exitButton);
	 
	//añadir a cada boton su funcion correspondiente
	newGameButton->connect([this]() {PlayGame();});
	loadGameButton->connect([this]() {LoadGame(); });
	exitButton->connect([this]() {Exit();});
}

void MainMenuState::Render() const {
	//clear de la pantalla(si se va a repintar toda la pantalla opcional)
	game->RenderClear();

	//render del background
	game->getTexture(MAINMENU)->render();

	//render de los gameObjects
	GameState::Render();
}

void MainMenuState::PlayGame() {
	game->getGameStateMachine()->pushState(new PlayState(game));
}

void MainMenuState::Exit() {
	game->getGameStateMachine()->popState();
}

void MainMenuState::LoadGame() {
	game->getGameStateMachine()->pushState(new ReadCodeState(game, this));
}

void MainMenuState::ReturnFromReadCode(std::string codeNumber) {
	try {
		game->getGameStateMachine()->pushState(new PlayState(game,"partidas_guardadas/save" + codeNumber + ".txt"));

	}
	catch (FileNotFoundError error) {
		SDL_ShowSimpleMessageBox(0, "Untitled", error.what(), nullptr);

	}
}