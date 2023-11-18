#ifndef ALIEN_H_
#define ALIEN_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"



constexpr int ALIENS_LIMIT_Y = 380;//500 posicion cañon


class Game;

class Alien : public SceneObject {

protected: 

	int type;

	Texture* texture;

	Mothership* mother;

	//para la animacion
	int frame;

	//velocidades de movimiento
	const static int velocityX = 26;//movimiento horizontal
	const static int velocityY = 10;//movimiento vertical


	//gestion de diferentes frame rates, movimiento
	int _currentMoveFrame = 0;
	static int _moveFrameRate;


	void UpdateAnim();

	void Move();

public:

	//constructor por parametros
	Alien(Game* game, Texture* text, Mothership* mother, Point2D<> _pos, int _type);

	//constructor por lectura de archivo
	Alien(Game* game, Texture* text,Mothership* mother, std::istream& in);

	//metodos heredados
	void Render() const override;

	void Update() override;
	
	bool Hit(SDL_Rect rect, char tLaser) override;

	void Save(std::ostream& out) const override;

	//destructor vacio
	~Alien() override {};

	//para random Mode
	void setType(int t) { type = t; };

	SDL_Rect getRect()const;

	int getType()const { return type; }

	//disminuye el frame rate del movimiento
	static void IncreaseVelocity();

	//para la carga de partidas

	void setPos(Point2D<> p) { pos = p; }
};


#endif // !ALIEN_H_

