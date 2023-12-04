#ifndef GameState_H_
#define GameState_H_

#include  "checkML.h"

#include <SDL.h>
#include <iostream>
#include <list>


#include "gameList.h"
#include "GameObject.h"

#include "EventHandler.h"

class PlayState;

class GameState {

protected:

	PlayState* game;

	GameList<GameObject, true> gameObjects;

	std::list<EventHandler*> handleEventsObjects;

public:

	
	void Render() const ;

	void Update();

	void HandleEvent(const SDL_Event& ev);


	void addEventListener();

	void addObject();



};



#endif // !GameState_H_

