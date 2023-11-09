#ifndef LASER_H_
#define LASER_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"//solo si se va a usar una textura para renderizar
#include "Vector2D.h"

#include "checkML.h"

class Game;


class Laser {
private:
	
	Point2D<> pos;
		
	bool originAlien;

	Vector2D<> velocityVector;

	
	Game* game;

	const static int WIDTH = 4;
	const static int HEIGHT = 18;


	static const int alienLaserVel = 4;
	static const int playerLaserVel = 12;
	int velocity;

	bool hited = false;

	//gestion de diferentes frame rates
	int _currentFrame = 0;
	const static int _frameRate = 2;

	void Move();
	bool Colisions();

public:

	Laser(Point2D<> _pos, bool originA, Game* _game)
 		:pos(_pos), originAlien(originA), game(_game),velocityVector(0, originAlien ? 1 :-1),
		velocity(originAlien ? alienLaserVel : playerLaserVel) {};

	void Render();

	bool Update();

	void Hit();

	SDL_Rect getRect()const;

	bool getOriginA()const { return originAlien; }
};



#endif // !LASER_H_  

