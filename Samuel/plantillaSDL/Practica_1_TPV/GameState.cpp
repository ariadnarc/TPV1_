#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Game.h"

void GameState::Render() const {
	GameList<GameObject,true>::forward_iterator it = gameObjects.begin();

	while (it != gameObjects.end()) {
		(*it).Render();
		++it;
	}

}

void GameState::Update() {
	GameList<GameObject, true>::forward_iterator it = gameObjects.begin();

	while (it != gameObjects.end()) {
		(*it).Update();
		++it;
	}
}

void GameState::HandleEvent(const SDL_Event& ev){
	std::list<EventHandler*>::iterator it = handleEventsObjects.begin();

	while (it != handleEventsObjects.end()) {
		(*it)->handleEvent(ev);
		++it;
	}
}


void GameState::addEventListener(EventHandler* handler) {
	handleEventsObjects.push_back(handler);
}

void GameState::addObject(GameObject* gameObject) {
	gameObjects.push_back(gameObject);
}

SDL_Renderer* GameState::getRenderer() { return game->getRenderer(); }