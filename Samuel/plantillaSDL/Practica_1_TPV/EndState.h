#ifndef EndState_H_
#define EndState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Button.h"

class EndState : public GameState {

	
	Button* returnToMenuButton;
	Button* exitButton;

	bool win;

	void ReturnToMenu();
	void Exit();

public:

	EndState(Game* game,bool win);

	void Render()const override;


};


#endif // !EndState_H_

