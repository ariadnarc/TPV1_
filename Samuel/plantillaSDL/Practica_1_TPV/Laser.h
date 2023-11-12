#ifndef LASER_H_
#define LASER_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"//solo si se va a usar una textura para renderizar
#include "Vector2D.h"
#include "SceneObject.h"

#include "checkML.h"

class Game;


class Laser : public SceneObject {
private:	
		
	char color;

	Vector2D<> velocityVector;

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

	Laser(Point2D<> _pos, char color, Game* _game)
 		: SceneObject(game,_pos,WIDTH,HEIGHT,1), color(color), velocityVector(0, color == 'r' ? 1 : -1),
		velocity(color == 'r' ? alienLaserVel : playerLaserVel) {};

	void Render() const override;

	void Update() override;

	void Hit(SDL_Rect rect, char tLaser) override;

	SDL_Rect getRect()const;

	bool getOriginA()const { return color == 'r'; }
};



#endif // !LASER_H_  

