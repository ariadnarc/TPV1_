#include "checkML.h"
#include "SDL.h"
#include "MotherShip.h"
#include "Game.h"
#include <iostream>

MotherShip::MotherShip(Game* game) : GameObject(game){
	//inicializa sin lectura
}

MotherShip::MotherShip(Game* game, std::istream& in) : GameObject(game){
	//inicializa con istream
}

void MotherShip::Initialize() {

}

void MotherShip::Initialize(std::istream& in) {

}

void MotherShip::Save(std::ostream& out) {

}

