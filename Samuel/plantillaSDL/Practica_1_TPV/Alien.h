#ifndef ALIEN_H_
#define ALIEN_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"


class PlayState;

class Alien : public SceneObject {

protected: 

	int type;

	Texture* texture;

	Mothership* mother;

	//para la animacion
	int animFrame;
	

	void UpdateAnim();

	void Move();

public:

	//constructor por parametros
	Alien(PlayState* game, Texture* text, Mothership* mother, Point2D<> _pos, int _type);

	//constructor por lectura de archivo
	Alien(PlayState* game, Texture* text,Mothership* mother, std::istream& in);

	//metodos heredados,override
	void Render() const override;

	void Update() override;
	
	bool Hit(SDL_Rect rect, char tLaser) override;

	void Save(std::ostream& out) const override;

	//destructor vacio
	~Alien() override {};


	int getType() const { return type; }

	//para random Mode, esto habra que cambiarlo
	void setType(int t) { type = t; };
};


#endif // !ALIEN_H_

