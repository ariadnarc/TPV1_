#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Game.h"
#include "Mothership.h"



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


void Mothership::Save(std::ostream& out)const {

	out << 3 << " ";

	out << state << " " << level << " " << _currentFrame << " ";

	out << '\n';

}