#include <iostream>
#include "SDL.h"
#include "Alien.h"
#include "Game.h"

#include "checkML.h"

int Alien::_moveFrameRate = 13;

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

	_currentMoveFrame++;
	if (_currentMoveFrame >= _moveFrameRate) {
		UpdateAnim();
		Move();
		
		_currentMoveFrame = 0;
	}

	_currentShootFrame++;
	if(_currentShootFrame >= _shootFrameRate){
		Shoot();
	
		_currentShootFrame = 0;
	}

	return alive;
}

void Alien::Hit() {
	alive = false;
}


void Alien::Move() {
	Vector2D<> dir = game->getDirection();
	
	pos = Vector2D<>(pos.getX() + dir.getX()*velocityX,pos.getY()+dir.getY()*velocityY);

	if (
		( dir.getX() == -1 && pos.getX() <= (0+velocityX) ) ||
		( dir.getX() ==  1 && pos.getX() >= (game->getWinWidht() - (texture->getFrameWidth() ) - velocityX) )
		) 
	{
		game->cannotMove();
	}
	if (dir.getY() == 1) {
		game->goDown();
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

void Alien::IncreaseVelocity() {
	_moveFrameRate--;
}