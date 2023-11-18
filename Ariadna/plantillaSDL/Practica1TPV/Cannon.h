#pragma once
#include "checkML.h"
#include "SDL.h"
#include <iostream>
#include "texture.h"
#include "Vector2D.h"

class Game;

class Cannon {
private:
	Point2D<> pos;

	Texture* texture;

	Game* game;

	int currentTime = 0, shootingTime = 5;

	Vector2D<> direction;

	const int velocity = 10;
	int lifesLeft;

	bool izqda = false, dcha = false, espacio = false;

	void Move();

	void Shoot(); //harán falta variables para el shoot
public:

	Cannon(Texture* text, Point2D<> _pos, Game* _game, int lifes)
		: texture(text), pos(_pos), game(_game), lifesLeft(lifes), direction(0, 0) {};

	void Render()const;

	bool Update();

	void HandleEvents(SDL_Event ev); // necesitaremos variables para el handleEvents

	void Hit();

	SDL_Rect GetRect() const;

	int GetLifes();
};
