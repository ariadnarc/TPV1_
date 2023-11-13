#include <iostream>
#include "SDL.h"
#include "ShooterAlien.h"
#include "Game.h"


#include "checkML.h"


ShooterAlien::ShooterAlien(Texture* text, Point2D<> _pos, int _type, Game* _game, Mothership* mother)
	: Alien(text, _pos, _type, _game, mother) {
	_shootFrameRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
}

void ShooterAlien::Shoot() {

	_currentShootFrame++;

	if (_currentShootFrame >= _shootFrameRate) {

		game->fireLaser(Vector2D<>(pos.getX() + texture->getFrameWidth() / 2, pos.getY() + texture->getFrameHeight() / 2), 'r');

		_shootFrameRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
		_currentShootFrame = 0;
	}
	
}

void ShooterAlien::Update() {

	Alien::Update();

	Shoot();
	
}