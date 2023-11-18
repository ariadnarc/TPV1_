#ifndef BUNKER_H_
#define BUNKER_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"

#include "checkML.h"


class Bunker {

	Point2D<> pos;

	int lifesLeft;

	Texture* texture;

public:

	//constructor
	Bunker(Texture* text,Point2D<> _pos,int lifes) 
		:texture(text), pos(_pos),lifesLeft(lifes){};


	void Render()const;

	bool Update();


	void Hit();	

	SDL_Rect getRect()const;
};





#endif // !BUNKER_H_
