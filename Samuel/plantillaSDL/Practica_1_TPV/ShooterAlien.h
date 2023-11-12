#ifndef ShooterAlien_H_
#define ShooterAlien_H_

#include <iostream>
#include <SDL.h>

#include "Alien.h"


#include "checkML.h"


class ShooterAlien : public Alien {

	int shootRate;
	int shootReload = 0;



	void Shoot();

};



#endif // !ShooterAlien_H_

