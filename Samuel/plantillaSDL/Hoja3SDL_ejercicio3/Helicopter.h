#ifndef Helicopter_H_
#define Helicopter_H_

#include "checkML.h"

#include "SDL.h"
#include <iostream>
#include "Texture.h"

class Helicopter {

	int winWidth;

	Texture* textura;

	SDL_Rect source;
	SDL_Rect destiny;

	int nAnimationFrames;
	int currentAnimFrame;
	double scale;

	int velocity;

public:

	void Render()const ;
	void SetPosition(int x, int y);
	void UpdateAnim();
	//constructor
	Helicopter(Texture* texture, int nAnimFrames, double _scale, int winwidht);

	void Update();

	//getters
	int getX() { return destiny.x; }
	int getY() { return destiny.y; }

	//setters
	void setVelocity(int v) { velocity = v; };

	void HandleEvents(SDL_Event& ev);

};



#endif // !Helicopter_H_