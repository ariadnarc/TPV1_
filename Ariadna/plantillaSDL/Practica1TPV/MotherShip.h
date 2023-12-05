#pragma once

#include "SDL.h"
#include "checkML.h"
#include "GameObject.h"
#include <iostream>
#include "Vector2D.h"

class MotherShip : public GameObject {

	Vector2D<> Aliensdir;

	bool _cannotMove = false;

	bool shouldmove = false;

	int waitingframes;
	int frameRate = 13;

	int bajadas;
	int nAliens;

	const int initialFrameRate = 14;
	const double increaseRate = 2.25;//percentage

	enum state { right, right_down, left, left_down };

	state currentState;

	// enum con los estados, preguntar por cómo funcionan




public:

	//Constructora e initialize por paso de parámetros
	MotherShip(Game* game);
	void Initialize();
	
	//Constructora e initialize por lectura de archivos
	MotherShip(Game* game, std::istream& in);
	void Initialize(std::istream& in);

	Vector2D<> getDirection() const { return Aliensdir; };


	bool shouldMove() const { return shouldMove; };

	void cannotMove() { _cannotMove = true; };

	void alienDied() { nAliens--; };

	void addAlien() { nAliens++; };

	void alienLanded();

	bool haveLanded();

	int getAlienCount() const { return nAliens; };

	void increaseAlienCount() { nAliens++; }

	// sobresscribe los metodos heredados de GameObject
	void Render() const override {};

	// control de tiempo con framerate y waitingframes. Actualizar estados y framerate
	void Update() override;

	//guardado de partida 
	void Save(std::ostream& out)const override;


	// el bool shouldmove se pone a true cuando el tiempo de espera sea igual a cero
	bool ShouldMove() const { return shouldmove; } // por qué es const?

	// cambia la direccion dependiendo del estado
	void UpdateDirection();
};