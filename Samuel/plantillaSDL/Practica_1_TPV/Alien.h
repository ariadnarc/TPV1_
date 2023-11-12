#ifndef ALIEN_H_
#define ALIEN_H_

#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "SceneObject.h"
#include "Mothership.h"


#include "checkML.h"

constexpr int ALIENS_LIMIT_Y = 380;//500 posicion cañon


class Game;

class Alien : public SceneObject {

protected: 
	int type;

	Texture* texture;

	Mothership* mother;

	//para la animacion
	int frame;

	const static int velocityX = 26;//movimiento horizontal
	const static int velocityY = 10;//movimiento vertical

	const static int MIN_SHOOT_RATE = 15;
	const static int MAX_SHOOT_RATE = 40;

	//gestion de diferentes frame rates
	int _currentMoveFrame = 0;

	static int _moveFrameRate;

	//diferente frame rate para el shoot
	int _currentShootFrame = 0;
	const static int _shootFrameRate = 5;

	void UpdateAnim();

	void Move();


public:

	//constructor
	Alien(Texture* text, Point2D<> _pos, int _type, Game* _game);

	//metodos heredados
	void Render() const override;

	void Update() override;
	
	void Hit(SDL_Rect rect, char tLaser) override;

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

