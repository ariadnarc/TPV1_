#ifndef ReadCodeState_H_
#define ReadCodeState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "Font.h"

class ReadCodeState : public GameState {

	PauseState* previousPauseState = nullptr;
	MainMenuState* previousMainMenuState = nullptr;

	Font* font;

	Texture* textoCodigoTexture;

	Texture* codeTexture = nullptr;

	int codeNumber = 0;
	int nDigits = 0;

public:

	ReadCodeState(Game* game,PauseState* previous);
	ReadCodeState(Game* game,MainMenuState* previous);

	~ReadCodeState();

	void Render() const override;

	void HandleEvent(const SDL_Event& ev) override;
};




#endif // !ReadCodeState_H_
