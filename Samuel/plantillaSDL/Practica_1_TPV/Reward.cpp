#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "Reward.h"
#include "PlayState.h"

Reward::Reward(PlayState* game, Point2D<> pos,  int lifesLeft,Texture* texture,Callback callback) 
	:SceneObject(game,pos,width,height,lifesLeft),texture(texture),callback(callback) {
	
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

void Reward::Update() {

	waitingFrames--;
	if (waitingFrames <= 0) {
		waitingFrames = _frameRate;
		Move();
	}

	//si colisionamos con el player
	if (playState->mayGrantReward(getRect())) {
		//llamar al callBack
		callback();

		//eliminar este objeto	playState->HasDied(gameObjectAnchor);
		playState->HasDied(sceneAnchor);
	}
	else if (pos.getY() > winHeight) {
		//eliminar este objeto
		playState->HasDied(sceneAnchor);
	}
}



void Reward::Move() {
	pos = pos + (Vector2D<>(0,1) * velocity);
}

void Reward::Render() const {

	SDL_Rect aux = getRect();
	texture->render(aux);
}