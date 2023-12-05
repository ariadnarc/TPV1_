#pragma once
#include "checkML.h"
#include "texture.h"
#include "SceneObject.h"
#include "Vector2D.h"
#include "Mothership.h"
#include "SDL.h"
#include <iostream>

class Game;

class Alien : public SceneObject {
private:
	Point2D<> pos;

	int type;

	Texture* texture;
	MotherShip* mother;
	Game* game;

	const int velocityX = 5;
	const int velocityY = 20;

	const static int MIN_TIME = 30;
	const static int MAX_TIME = 60;

	int currenttime = 0, shootingtime;

	bool alive;

	int frame;

	void updateAnim();

	void Move();

	void Shoot();//harán falta variables para el shoot
public:
	//constructora sin paso de archivos
	Alien(Texture* text, Point2D<> _pos, int _type, Game* _game, MotherShip* mother);

	void Render()const;

	SDL_Rect GetRect() const;

	void Update();

	bool Hit();
};