#include "checkML.h"


#include "Helicopter.h";
#include "SDL.h"
#include <iostream>
#include "Texture.h"



void Helicopter::Render() const{
	textura->Render(&source, &destiny);
}

void Helicopter::SetPosition(int x, int y) {
	destiny.x = x;
	destiny.y = y;
}

Helicopter::Helicopter(Texture* texture, int nAnimFrames, double _scale, int winwidht)
	: textura(texture), nAnimationFrames(nAnimFrames), currentAnimFrame(0), scale(_scale), winWidth(winwidht)
{
	source.x = 0; source.y = 0;

	source.w = texture->getWidht() / nAnimationFrames;
	source.h = texture->getHeight();

	destiny.x = 0; destiny.y = 0;

	destiny.w = source.w * scale;
	destiny.h = source.h * scale;
};


void Helicopter::UpdateAnim() {
	currentAnimFrame = (currentAnimFrame + 1) % nAnimationFrames;
	source.x = source.w * currentAnimFrame;
}

void Helicopter::Update() {

	SetPosition((destiny.x + (winWidth - velocity)) % winWidth, destiny.y);
	UpdateAnim();
}