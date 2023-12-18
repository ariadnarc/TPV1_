#ifndef PauseState_H_
#define PauseState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "Button.h"

class PauseState : public GameState {

	Button* continueGameButton;
	Button* saveGameButton;
	Button* loadGameButton;
	Button* exitButton;

	PlayState* previusPlayState;

	void Continue();
	void SaveGame();
	void LoadGame();
	void Exit();
public:

	PauseState(Game* game,PlayState* previusPlayState);

	 void Render() const override;

};


#endif // !PauseState_H_
