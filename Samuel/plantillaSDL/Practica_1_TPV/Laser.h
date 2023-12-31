#ifndef LASER_H_
#define LASER_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "texture.h"//solo si se va a usar una textura para renderizar
#include "Vector2D.h"
#include "SceneObject.h"


class PlayState;

class Laser : public SceneObject {
private:	
		
	char color;

	Vector2D<> velocityVector;

	const static int WIDTH = 4;
	const static int HEIGHT = 18;


	static const int alienLaserVel = 2;
	static const int playerLaserVel = 8;
	int velocity;

	//gestion de diferentes frame rates
	int waitingFrames = 0;
	const static int _frameRate = 1;

	void Move();
	bool Colisions();

public:

	//constructor por parametros
	Laser(PlayState* game, Point2D<> pos, char color);

	//constructor por lectura de archivos
	Laser(PlayState* game, std::istream& in);

	void Render() const override;

	void Update() override;

	void Save(std::ostream& out) const override;

	char getColor()const { return color; }

	bool Hit(SDL_Rect rect, char tLaser) override;

};

#endif // !LASER_H_  