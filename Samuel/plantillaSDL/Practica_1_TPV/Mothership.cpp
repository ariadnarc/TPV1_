#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Game.h"
#include "Mothership.h"


//constructor por paso de parametros
Mothership::Mothership(Game* game) 
	: GameObject(game) {};

//constructor por lectura de archivo, no se usa
Mothership::Mothership(Game* game, std::istream& in) 
	: GameObject(game){
	
	int aux;

	//solo para que funcione
	int x, y;
	in >> x >> y;
	in >> aux >> level >> waitingFrames;

	currentState = (state)aux;

}

void Mothership::InitializeMother(std::istream& in) {
	int aux;

	//solo para que funcione
	int x, y;
	in >> x >> y;
	in >> aux >> level >> waitingFrames;

	currentState = (state)aux;

	if (currentState == right) aliensDir = Vector2D<>(1, 0);
	else if(currentState == left)aliensDir = Vector2D<>(-1, 0);
	else aliensDir = Vector2D<>(0, -1);
}

void Mothership::Save(std::ostream& out)const {

	out << MOTHERSHIP << " ";

	out << currentState << " " << level << " " << waitingFrames << " ";

	out << '\n';

}



void Mothership::alienLanded() {
	//llamar al game
}

void Mothership::haveLanded() {

}

void Mothership::Update() {
	
	--waitingFrames;

	_shouldMove = (waitingFrames <= 0);

	if (_shouldMove) {
		
		waitingFrames = moveFrameRate;

		if (_cannotMove) {
			currentState = (state)(((int)currentState + 1) % 4);
			aliensDir = Vector2D <>(0, 1);
			_cannotMove = false;
			level++;
		}
		else if (currentState == left_down) {
			currentState = (state)(((int)currentState + 1) % 4);
			aliensDir = Vector2D <>(1, 0);
		}
		else if (currentState == right_down) {
			currentState = (state)(((int)currentState + 1) % 4);
			aliensDir = Vector2D<>(-1, 0);
		}
	}
	
}


