#ifndef Dog_H_
#define Dog_H_

#include "checkML.h"

#include "SDL.h"
#include <iostream>
#include "Texture.h"


class Game;

class Dog {

	Game* game;

	int winWidth;

	Texture* textura;

	SDL_Rect source;
	SDL_Rect destiny;

	int nAnimationFrames;
	int currentAnimFrame;
	double scale;

	int velocity;

	bool move = false;

public:

	void Render()const;
	void SetPosition(int x,int y);
	void UpdateAnim();
	//constructor
	Dog(Texture* texture,int nAnimFrames,double _scale,int winwidht);

	void Update();

	//getters
	int getX() { return destiny.x; }
	int getY() { return destiny.y; }

	//setters
	void setVelocity(int v) { velocity = v; };

	void Move();

	void HandleEvents(SDL_Event& ev);
};



#endif // !Dog_H_

