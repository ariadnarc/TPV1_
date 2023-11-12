#include <iostream>
#include "SDL.h"
#include "ShooterAlien.h"
#include "Game.h"


#include "checkML.h"


void ShooterAlien::Shoot() {
		
	if (type == 0) {
		shootReload++;

		if (shootReload >= shootRate) {
			game->fireLaser(Vector2D<>(pos.getX() + texture->getFrameWidth() / 2, pos.getY() + texture->getFrameHeight() / 2), true);
			shootReload = 0;
			shootRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
		}
	}
	
	
}