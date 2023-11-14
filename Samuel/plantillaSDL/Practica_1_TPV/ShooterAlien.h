#ifndef ShooterAlien_H_
#define ShooterAlien_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>

#include "Alien.h"




class ShooterAlien : public Alien {

	//ajustar valores
	const static int MIN_SHOOT_RATE = 75;
	const static int MAX_SHOOT_RATE = 200;

	//diferente frame rate para el shoot
	int _currentShootFrame = 0;
	int _shootFrameRate;

	void Shoot();

public:

	//constructor
	ShooterAlien(Texture* text, Point2D<> _pos, int _type, Game* _game, Mothership* mother);



	void Update() override;
};



#endif // !ShooterAlien_H_

