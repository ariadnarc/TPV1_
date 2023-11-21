#pragma once

#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include <list>

#include "GameObject.h"
#include "Vector2D.h"

class SceneObject : public GameObject {
protected:

	Game* game;

	Point2D<> pos;

	int width;
	int height;

	// si no se le da otro valor como el bunker o el player, todos los objetos tienen 1 vida
	int lifesleft = 1;

	// aqui va el iterator que no se que es


public:

	virtual bool Hit(SDL_Rect rect, char tlaser) = 0;

	// Constructora por parámetros
	SceneObject(Game* game, Point2D<> pos, int width, int height, int lifesleft);

	// Constructora por lectura de archivos
	SceneObject(Game* game, std::istream& in);

	virtual void Save(std::ostream& out) const;

	SDL_Rect GetRect() const;

	//FALTA:
	// destructora?

	// setlistiterator
};
