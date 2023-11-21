#ifndef CANON_H_
#define CANON_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"
#include "SceneObject.h"



class Game;

class Cannon : public SceneObject{

	Texture* texture;

	Vector2D<> direction;

	const int velocity = 2;

	//booleanos para control del input,cambiar por el otro metodo
	bool rightWASD = false;
	bool rightArrow = false;
	bool leftWASD = false;
	bool leftArrow = false;
	bool space = false;

	const int SHOOT_RATE = 25;

	int shootReload = 0;

	//gestion de diferentes frame rates
	int waitingFrames = 0;
	const static int _frameRate = 1;


	void Move();

	void Shoot();

public:

	//constructor por parametros
	Cannon(Game* game, Texture* text, Point2D<> pos, int lifes);

	//constructor por lectura de archivo
	Cannon(Game* game, Texture* text, std::istream& in);

	void Render()const override;

	void Update() override;

	void HandleEvents(SDL_Event ev); 

	bool Hit(SDL_Rect rect, char tLaser) override;

	int getLifes() const { return lifesLeft; }

	SDL_Rect getRect()const ;


	//para la carga de partidas
	void setPos(Point2D<> p) { pos = p; }

	void setLifes(int n) { lifesLeft = n; }


	void Save(std::ostream& out) const override;
};



#endif // !CANON_H_

