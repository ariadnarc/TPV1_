#ifndef MainMenuState_H_
#define MainMenuState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Button.h"

class MainMenuState : public GameState {

	Button* newGameButton;
	Button* loadGameButton;
	Button* exitButton;



public:
	
	MainMenuState(Game* game);

	void Render() const override;


	void PlayGame();

	void Exit();
};


#endif // !MainMenuState_H_
