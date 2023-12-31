#ifndef MainMenuState_H_
#define MainMenuState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Button.h"
#include "Font.h"

class MainMenuState : public GameState {

	Button* newGameButton;
	Button* loadGameButton;
	Button* exitButton;


	void PlayGame();

	void Exit();

	void LoadGame();

public:
	
	MainMenuState(Game* game);

	void Render() const override;

	void ReturnFromReadCode(std::string codeNumber);

};


#endif // !MainMenuState_H_
