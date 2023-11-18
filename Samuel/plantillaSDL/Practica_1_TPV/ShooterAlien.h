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

	//constructor por parametros
	ShooterAlien(Game* game, Texture* text, Mothership* mother, Point2D<> pos, int type);

	//constructor por lectura de archivo
	ShooterAlien(Game* game, Texture* text, Mothership* mother, std::istream& in);

	void Save(std::ostream& out) const override;


	void Update() override;
};



#endif // !ShooterAlien_H_

