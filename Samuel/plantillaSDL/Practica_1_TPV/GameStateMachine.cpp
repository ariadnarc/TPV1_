#include "checkML.h"

#include <iostream>
#include <SDL.h>


#include "GameStateMachine.h"
#include "MainMenuState.h"

//constructor
GameStateMachine::GameStateMachine() {

	//inicializamos la pila con el estado del menu inicial
	gameStack.push(new MainMenuState());
}

//destructor
GameStateMachine::~GameStateMachine() {

	//destruye uno a uno todos los estados apilados que queden
	while (!gameStack.empty()) {
		delete gameStack.top();
		gameStack.pop();
	}

}


void GameStateMachine::Render() const{
	gameStack.top()->Render();
}

void GameStateMachine::Update() {
	gameStack.top()->Update();
}

void GameStateMachine::HandleEvents(const SDL_Event& ev) {
	gameStack.top()->HandleEvent(ev);
}


void GameStateMachine::pushState(GameState* state) {
	gameStack.push(state);
}

void GameStateMachine::replaceState(GameState* state) {
	popState();
	pushState(state);
}

void GameStateMachine::popState() {
	delete gameStack.top();
	gameStack.pop();
}