#ifndef CANON_H_
#define CANON_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"

#include "checkML.h"


class Game;

class Cannon {

	Point2D<> pos;

	Texture* texture;

	Game* game;

	Vector2D<> direction;

	int lifesLeft;

	const int velocity = 10;


	//booleanos para control del input
	bool rightWASD = false;
	bool rightArrow = false;
	bool leftWASD = false;
	bool leftArrow = false;
	bool space = false;

	const int SHOOT_RATE = 5;

	int shootReload = 0;

	void Move();

	void Shoot();

public:

	//constructor
	Cannon(Texture* text, Point2D<> _pos, Game* _game,int lifes)
		:texture(text), pos(_pos),  game(_game),lifesLeft(lifes), direction(0,0) {};


	void Render()const;

	bool Update();

	void HandleEvents(SDL_Event ev); 

	void Hit();

	int getLifes() const { return lifesLeft; }

	SDL_Rect getRect()const ;
};



#endif // !CANON_H_

