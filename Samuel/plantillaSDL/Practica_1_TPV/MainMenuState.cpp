#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "MainMenuState.h"
#include "Game.h"
#include "PlayState.h"

MainMenuState::MainMenuState(Game* game) 
	: GameState(game), 
	newGameButton(new Button(this, game->getTexture(NUEVA_PARTIDA), Point2D<>(300, 150))), 
	loadGameButton(new Button(this, game->getTexture(CARGAR_PARTIDA), Point2D<>(292,200))),
	exitButton(new Button(this, game->getTexture(SALIR), Point2D<>(345, 250)))
{
	addObject(newGameButton);
	addObject(loadGameButton);
	addObject(exitButton);

	addEventListener(newGameButton);
	addEventListener(loadGameButton);
	addEventListener(exitButton);
	 
	newGameButton->connect([this]() {PlayGame();});
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