#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "Bomb.h"
#include "PlayState.h"
#include "Game.h"

Bomb::Bomb(PlayState* game, Point2D<> pos,int lifesLeft,Texture* texture) 
		:SceneObject(game,pos,width,height,lifesLeft), texture(texture) {

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}

void Bomb::Move() {
	pos = pos + (Vector2D<>(0, 1) * velocity);
}
bool Bomb::Colisions() {
	return playState->collisions(this);
}

void Bomb::Update() {

	if (lifesLeft <= 0) return;

	waitingFrames--;

	if (waitingFrames <= 0) {
		waitingFrames = _frameRate;
		Move();
	}

	if (pos.getY() > winHeight || Colisions()) {
		//eliminar este objeto
		playState->HasDied(sceneAnchor);
	}
}

void Bomb::Render()const {

	SDL_Rect target = getRect();

	texture->render(target);
}

bool Bomb::Hit(SDL_Rect rect, char tLaser) {
	if (lifesLeft <= 0) return false;

	bool colision = false;

	SDL_Rect aux = getRect();


	if (tLaser == 'b') {
		if (SDL_HasIntersection(&rect, &aux)) {
			colision = true;
			lifesLeft--;
			if (lifesLeft <= 0) playState->HasDied(sceneAnchor);
		}
	}

	return colision;
}