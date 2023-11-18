#ifndef BUNKER_H_
#define BUNKER_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"
#include "SceneObject.h"



class Bunker : public SceneObject{

	Texture* texture;

public:

	//constructor por parametros
	Bunker(Game* game, Texture* text, Point2D<> _pos, int lifes);

	//constructor por lectura de archivo
	Bunker(Game* game, Texture* text, std::istream& in);
	
	void Render()const override;

	void Update() override;


	bool Hit(SDL_Rect rect, char tLaser) override;

	SDL_Rect getRect()const;

	int getLifes()const { return lifesLeft; }

	//para la carga de partidas
	void setPos(Point2D<> p) { pos = p; }

	void setLifes(int n) { lifesLeft = n; }

	void Save(std::ostream& out) const override;
};





#endif // !BUNKER_H_
