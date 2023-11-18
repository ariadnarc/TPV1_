#include <iostream>
#include "SDL.h"
#include "Alien.h"
#include "Game.h"

#include "checkML.h"


Alien::Alien(Texture* text, Point2D<> _pos, int _type, Game* _game)
	:texture(text), pos(_pos), type(_type), game(_game), alive(true), frame(0) {

	shootRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);

};


void Alien::Render() const {
	texture->renderFrame(getRect(), type, frame);
}

void Alien::UpdateAnim() {
	frame = (frame + 1) % texture->getNumColumns();
}

bool Alien::Update() {

	UpdateAnim();
	Move();
	Shoot();

	return alive;
}

void Alien::Hit() {
	alive = false;
}


void Alien::Move() {
	Vector2D<> dir = game->getDirection();
	
	pos = pos + dir*velocity;

	if (
		( dir.getX() == -1 && pos.getX() <= (0+velocity) ) ||
		( dir.getX() ==  1 && pos.getX() >= (game->getWinWidht() - (texture->getFrameWidth() ) - velocity) )
		) 
	{
		game->cannotMove();
	}

	if (pos.getY() >= ALIENS_LIMIT_Y) {
		game->aliensLimitBotton();
	}

}

void Alien::Shoot() {
	if (type == 0) {
		shootReload++;

		if (shootReload >= shootRate) {
			game->fireLaser(Vector2D<>(pos.getX() + texture->getFrameWidth() / 2, pos.getY() + texture->getFrameHeight() / 2), true);
			shootReload = 0;
			shootRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
		}


	}
}

SDL_Rect Alien::getRect()const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	return rect;
}