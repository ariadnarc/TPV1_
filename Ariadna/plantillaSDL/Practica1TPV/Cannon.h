#pragma once
#include "checkML.h"
#include "SDL.h"
#include <iostream>
#include "texture.h"
#include "Vector2D.h"

class Game;

class Cannon {
private:

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
	Cannon(PlayState* game, Texture* text, Point2D<> pos, int lifes);

	//constructor por lectura de archivo
	Cannon(PlayState* game, Texture* text, std::istream& in);

	void Render()const override;

	void Update() override;

	void Save(std::ostream& out) const override;

	bool Hit(SDL_Rect rect, char tLaser) override;

	void handleEvent(const SDL_Event& ev)override;

	int getLifes() const { return lifesLeft; }
};
