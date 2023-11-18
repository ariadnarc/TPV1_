#pragma once
#include "checkML.h"
#include "Vector2D.h"
#include "SDL.h"
#include <iostream>"

const static int WIDTH = 3;
const static int HEIGHT = 15;

class Game;

class Laser {
private:

	Point2D<> pos;

	int vel = 8;

	Vector2D<> velocity;


	Game* game;

	void Move();

public:
	bool originAlien, alive = true;

	Laser(Point2D<> _pos, bool originA, Game* _game) 
		: pos(_pos), originAlien(originA), game(_game)
	{ 
		if (originAlien) {
		velocity = Vector2D<>(0, 1);
		}
		else {
			velocity = Vector2D<>(0, -1);
		} 
	};

	void Render();

	bool Update();

	SDL_Rect GetRect();

	void Hit();
};

