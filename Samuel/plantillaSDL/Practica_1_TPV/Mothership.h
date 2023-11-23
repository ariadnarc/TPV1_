#ifndef Mothership_H_
#define Mothership_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>

#include "GameObject.h"
#include "Vector2D.h"

constexpr int ALIENS_LIMIT_Y = 380;//500 posicion cañon

class Mothership : public GameObject {

	Vector2D<> aliensDir;

	bool _cannotMove = false;

	bool _shouldMove = false;


	enum state{right,right_down,left,left_down};

	state currentState;

	//para incremento de velocidad de los aliens
	int level;

	int waitingFrames;
	int moveFrameRate = 13;

	const int initialMoveFrameRate = 14;
	const double increaseRate = 2.25;//percentage

	//velocidades de movimiento de los aliens
	const static int velocityX = 26;//movimiento horizontal
	const static int velocityY = 10;//movimiento vertical

	int nAliens;

public://metodos, puede que esten mal los tipos o que haya que añadir parametros

	//constructor por paso de parametros, basico
	Mothership(Game* game);

	//constructor por lectura de archivo
	Mothership(Game* game, std::istream& in);

	void Initialize(std::istream& in);

	//getter de la direccion de movimiento de los aliens
	Vector2D<> getDirection() const { return aliensDir; };


	bool shouldMove() const { return _shouldMove; };

	void cannotMove() { _cannotMove = true; };

	void alienDied() { nAliens--; };

	//diferencia entre estos 2 metodos?
	void alienLanded();

	void haveLanded();

	int getAlienCount() const { return nAliens; };

	void increaseAlienCount() { nAliens++; }

	//override de metodos heredados
	void Render() const override {};
	void Update() override;
	void Save(std::ostream& out)const override;

	//getters de la velocidad
	int getVelocityX() const{ return velocityX; }
	int getVelocityY() const{ return velocityY; }

	void Initialize();

	void UpdateDirection();
};




#endif // !Mothership_H_

