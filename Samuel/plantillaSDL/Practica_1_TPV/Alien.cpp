#include <iostream>
#include "SDL.h"
#include "Alien.h"
#include "Game.h"


#include "checkML.h"

int Alien::_moveFrameRate = 13;

Alien::Alien(Texture* text, Point2D<> _pos, int _type, Game* _game,Mothership* mother)
	:SceneObject(game,_pos,0,0,1), texture(text), type(_type), frame(0),mother(mother) {

	//shootRate = game->getRandomRange(MIN_SHOOT_RATE, MAX_SHOOT_RATE);
};


void Alien::Render() const {
	texture->renderFrame(getRect(), type, frame);
}

void Alien::UpdateAnim() {
	frame = (frame + 1) % texture->getNumColumns();
}

void Alien::Update() {

	_currentMoveFrame++;
	if (_currentMoveFrame >= _moveFrameRate) {
		UpdateAnim();
		Move();
		
		_currentMoveFrame = 0;
	}

	/*pasar al shooterAlien
	_currentShootFrame++;
	if(_currentShootFrame >= _shootFrameRate){
		Shoot();
	
		_currentShootFrame = 0;
	}
	*/

	//return alive;
}

void Alien::Hit(SDL_Rect rect, char tLaser) {
	//alive = false;
}


void Alien::Move() {
	Vector2D<> dir = mother->getDirection();
	
	pos = Vector2D<>(pos.getX() + dir.getX()*velocityX,pos.getY()+dir.getY()*velocityY);

	
	if (
		( dir.getX() == -1 && pos.getX() <= (0+velocityX) ) ||
		( dir.getX() ==  1 && pos.getX() >= (game->getWinWidht() - (texture->getFrameWidth() ) - velocityX) )
		) 
	{
		mother->cannotMove();
	}
	if (dir.getY() == 1) {
		mother->goDown();
	}

	if (pos.getY() >= ALIENS_LIMIT_Y) {
		//game->aliensLimitBotton();
		mother->alienLanded();
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


void Alien::Save(std::ostream& out) const {

}
