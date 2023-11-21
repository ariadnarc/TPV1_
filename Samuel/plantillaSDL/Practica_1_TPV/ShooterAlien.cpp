#include "checkML.h"


#include <iostream>
#include "SDL.h"
#include "ShooterAlien.h"
#include "Game.h"



//constructor por parametros
ShooterAlien::ShooterAlien(Game* game, Texture* text, Mothership* mother, Point2D<> pos, int type)
	: Alien(game,text,mother,pos,type) {
	waitingShootFrames = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
}

//constructor por lectura de archivo
ShooterAlien::ShooterAlien(Game* game, Texture* text, Mothership* mother, std::istream& in) 
	: Alien(game,text,mother,in) {
	in >> waitingShootFrames;
}


void ShooterAlien::Save(std::ostream& out) const {

	out << SHOOTER_ALIEN << " ";

	Alien::Save(out);

	out << waitingShootFrames << " ";

	out << '\n';

}

void ShooterAlien::Shoot() {

	--waitingShootFrames;

	if (waitingShootFrames <= 0) {

		game->fireLaser(Vector2D<>(pos.getX() + texture->getFrameWidth() / 2, pos.getY() + texture->getFrameHeight() / 2), 'r');

		_shootFrameRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
		waitingShootFrames = _shootFrameRate;
	}
	
}

void ShooterAlien::Update() {

	if (lifesLeft <= 0) return;


	Alien::Update();

	Shoot();
	
}

