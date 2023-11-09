#ifndef ALIEN_H_
#define ALIEN_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"

#include "checkML.h"

constexpr int ALIENS_LIMIT_Y = 380;//500 posicion cañon


class Game;

class Alien {

	Point2D<> pos;

	int type;

	Texture* texture;

	Game* game;

	bool alive;

	int frame;

	const static int velocityX = 26;//movimiento horizontal
	const static int velocityY = 10;//movimiento vertical

	const static int MIN_SHOOT_RATE = 15;
	const static int MAX_SHOOT_RATE = 40;


	int shootRate;
	int shootReload = 0;

	//gestion de diferentes frame rates
	int _currentMoveFrame = 0;

	static int _moveFrameRate;

	//diferente frame rate para el shoot
	int _currentShootFrame = 0;
	const static int _shootFrameRate = 5;

	void UpdateAnim();

	void Move();

	void Shoot();

public:

	//constructor
	Alien(Texture* text, Point2D<> _pos, int _type, Game* _game);

	//para random Mode
	void setType(int t) { type = t; };

	void Render()const;

	bool Update();
	
	void Hit();

	SDL_Rect getRect()const;

	int getType()const { return type; }

	//disminuye el frame rate del movimiento
	static void IncreaseVelocity();

	//para la carga de partidas

	void setPos(Point2D<> p) { pos = p; }
};


#endif // !ALIEN_H_

