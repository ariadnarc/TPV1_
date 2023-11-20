#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Game.h"
#include "Mothership.h"


//constructor por paso de parametros
Mothership::Mothership(Game* game, Vector2D<> dir) 
	: GameObject(game), aliensDir(dir) {};

//constructor por lectura de archivo
Mothership::Mothership(Game* game, std::istream& in) 
	: GameObject(game){

	in >> state >> level >> _currentFrame;

	//asignar valores...

}

void Mothership::Save(std::ostream& out)const {

	out << MOTHERSHIP << " ";

	out << state << " " << level << " " << _currentFrame << " ";

	out << '\n';

}


bool Mothership::shouldMove() {

	return true;
}

void Mothership::cannotMove() {
	_cannotMove = true;	
}
void Mothership::goDown() {
	_goDown = true;
}


void Mothership::alienDied() {

}

void Mothership::alienLanded() {
	//llamar al game
}

void Mothership::haveLanded() {

}

void Mothership::Update() {

	/*
	_currentMoveFrame++;
	if (_currentMoveFrame >= _moveFrameRate) {
		
		//should move...
		_currentMoveFrame = 0;
	}
	*/


	if (_goDown) {
		aliensDir = Vector2D<>(nextDirX, 0);//no seria mejor con un set?
		_goDown = false;
	}

	if (_cannotMove) {
		nextDirX = aliensDir.getX() * -1;
		aliensDir = Vector2D<>(0, 1);
		_cannotMove = false;
	}

}


