#include "checkML.h"


#include "Dog.h";
#include "SDL.h"
#include <iostream>
#include "Texture.h"
#include "Game.h"


void Dog::Render()const {
	textura->Render(&source, &destiny);
}

void Dog::SetPosition(int x, int y) {
	destiny.x = x;
	destiny.y = y;
}

Dog::Dog(Texture* texture, int nAnimFrames,double _scale,int winwidht)
	: textura(texture), nAnimationFrames(nAnimFrames),currentAnimFrame(0), scale(_scale),winWidth(winwidht)
{	
	source.x = 0; source.y = 0;

	source.w = texture->getWidht() / nAnimationFrames;
	source.h = texture->getHeight();

	destiny.x = 0; destiny.y = 0;

	destiny.w = source.w * scale;
	destiny.h = source.h * scale;
};


void Dog::UpdateAnim() {
	currentAnimFrame = (currentAnimFrame + 1) % nAnimationFrames;
	source.x = source.w * currentAnimFrame;
}

void Dog::Update() {
	if(move) Move();
	UpdateAnim();
}

void Dog::Move() {
	SetPosition((destiny.x + velocity) % winWidth, destiny.y);
}

void Dog::HandleEvents(SDL_Event& ev) {
	if (ev.type == SDL_KEYDOWN) {
		if (ev.key.keysym.scancode = SDL_SCANCODE_D) {
			move = !move;
		}
	}
}