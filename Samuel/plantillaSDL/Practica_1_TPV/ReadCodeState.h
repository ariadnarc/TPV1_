#ifndef ReadCodeState_H_
#define ReadCodeState_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "GameState.h"
#include "PauseState.h"


class ReadCodeState : public GameState {

	PauseState* previousPauseState;

	

public:

	ReadCodeState(Game* game,PauseState* previous);

	void Render()const override;

};




#endif // !ReadCodeState_H_
