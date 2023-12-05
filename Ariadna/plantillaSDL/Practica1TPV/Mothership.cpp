#include "checkML.h"
#include "SDL.h"
#include "MotherShip.h"
#include "Game.h"
#include <iostream>

MotherShip::MotherShip(Game* game) : GameObject(game){
	Initialize();
}

MotherShip::MotherShip(Game* game, std::istream& in) : GameObject(game){
	Initialize(in);
}

void MotherShip::Initialize() {
	currentState = right;

	UpdateDirection();

	waitingframes = 0;
	bajadas = 0;
}

void MotherShip::Initialize(std::istream& in) {
	int aux;

	in >> aux >> bajadas >> waitingframes;

	currentState = (state)aux;

	//nAliens = 0;

	UpdateDirection();
}

void MotherShip::Save(std::ostream& out) const {
	//out << MOTHERSHIP << " ";

	out << currentState << " " << bajadas << " " << waitingframes << " ";

	out << '\n';
}

void MotherShip::Update() {

	// va disminuyendo los segundos que le quedan para moverse
	waitingframes--;

	shouldmove = (waitingframes <= 0); // cuando el tiempo de espera sea cero

	if (shouldmove) {
		waitingframes = frameRate; // cuando pueda moverse pone otra vez el tiempo de espera a su frame rate

		if (_cannotMove) {
			// actualiza el estado y su direccion
			currentState = (state)(((int)currentState + 1) % 4); // formula del siguiente
			//si no se podia mover es porque su siguiente direccion tiene que ser abajo durante 1 frame
			Aliensdir = Vector2D <>(0, 1);

			_cannotMove = false; // ahora si se puede mover

			//aumento del numero de veces que hayan bajado los aliens
			bajadas++;

			//incrementar el framerate
			frameRate = initialFrameRate * (1 - ((increaseRate * bajadas) / 100));

		}
		else if (currentState = left_down) {
			currentState = (state)(((int)currentState + 1) % 4); // formula del siguiente
			Aliensdir = Vector2D <>(1, 0); // cambio dir de los aliens a derecha

		}
		else if (currentState = right_down) {
			currentState = (state)(((int)currentState + 1) % 4); // formula del siguiente
			Aliensdir = Vector2D <>(-1, 0); // cambio dir de los aliens a izqda

		}
	}
}

void MotherShip::UpdateDirection() {
	if (currentState == right) Aliensdir = Vector2D<>(1, 0);
	else if (currentState == left)Aliensdir = Vector2D<>(-1, 0);
	else Aliensdir = Vector2D<>(0, -1);
};
