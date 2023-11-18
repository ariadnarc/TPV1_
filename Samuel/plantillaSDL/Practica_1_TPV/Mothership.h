#ifndef Mothership_H_
#define Mothership_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>

#include "GameObject.h"
#include "Vector2D.h"



class Mothership : public GameObject {

	Vector2D<> aliensDir;

	int nextDirX = 0;

	bool _cannotMove = false;

	//a lo mejor no hace falta
	bool _goDown = false;

	//enumerado state ...

	//level de descenso ...

	int state;
	int level;

	int _currentFrame;


public://metodos, puede que esten mal los tipos o que haya que añadir parametros

	//constructor por paso de parametros
	Mothership(Game* game,Vector2D<> dir);

	//constructor por lectura de archivo
	Mothership(Game* game, std::istream& in);

	Vector2D<> getDirection() const { return aliensDir; };

	bool shouldMove();

	void cannotMove();

	void alienDied();

	void alienLanded();

	void haveLanded();

	int getAlienCount();

	void Render() const override {};
	void Update() override;
	void Save(std::ostream& out)const override;


	void goDown();// no se si hace falta
};




#endif // !Mothership_H_

