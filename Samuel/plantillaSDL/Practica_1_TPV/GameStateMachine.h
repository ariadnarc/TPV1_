#ifndef GameStateMachine_H_
#define GameStateMachine_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include <stack>

#include "GameState.h"

class Game;

class GameStateMachine {

	Game* game;
	std::stack<GameState*> gameStack;

public:

	//constructor
	GameStateMachine(Game* game);

	//destructor
	~GameStateMachine();


	void pushState(GameState* state);
	void replaceState(GameState* state);
	void popState();

	void Render()const;
	void Update();
	void HandleEvents(const SDL_Event& ev);

};



#endif // !GameStateMachine_H_
