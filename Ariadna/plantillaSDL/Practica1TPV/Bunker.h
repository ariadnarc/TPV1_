#pragma once
#include "checkML.h"
#include "texture.h"
#include "Vector2D.h"
#include "GameObject.h"
#include "SDL.h"
#include <iostream>

class Bunker : public GameObject{
private:

	Point2D<> pos;

	int lifesLeft;

	Texture* texture;

public:

	Bunker(Texture* text, Point2D<> _pos, int lifes)
		: texture(text), pos(_pos), lifesLeft(lifes) {};

	void Render()const;

	//bool Update();  cambiar a void (todos los updates)

	void Hit();

	SDL_Rect GetRect() const;
};

