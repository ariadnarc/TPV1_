#ifndef BUNKER_H_
#define BUNKER_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"
#include "SceneObject.h"

#include "checkML.h"


class Bunker : public SceneObject{

	Texture* texture;

public:

	//constructor
	Bunker(Texture* text,Point2D<> _pos,int lifes) 
		:SceneObject(nullptr,_pos,0,0,lifes), texture(text) {};


	void Render()const override;

	void Update() override;


	void Hit(SDL_Rect rect, char tLaser) override;

	SDL_Rect getRect()const;

	int getLifes()const { return lifesLeft; }

	//para la carga de partidas
	void setPos(Point2D<> p) { pos = p; }

	void setLifes(int n) { lifesLeft = n; }

	void Save(std::ostream& out) const override;
};





#endif // !BUNKER_H_
