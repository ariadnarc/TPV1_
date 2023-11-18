#include "checkML.h"
#include "SDL.h"
#include "Game.h"
#include <iostream>
#include "Alien.h"


Alien::Alien(Texture* text, Point2D<> _pos, int _type, Game* _game)
: texture(text), pos(_pos), type(_type), game(_game), alive(true), frame(0) 
{
	shootingtime = game->getRandomRange(MIN_TIME, MAX_TIME);


};

void Alien::Render()const {

	texture->renderFrame(GetRect(), type, frame);
}

void Alien::updateAnim() {
	frame = (frame + 1) % texture->getNumColumns();
}

bool Alien::Update() {

	updateAnim();

	Move();

	Shoot();

	currenttime++;

	return alive;
}

void Alien::Hit() {

	alive = false;
}

void Alien::Move() {

	pos = Vector2D<>(pos.getX() + game->GetDirection().getX() * velocityX, pos.getY() + game->GetDirection().getY() * velocityY);

	//si no va a poder moverse llama al cannotMove del Game
	if (game->GetDirection().getX() == 1 && pos.getX() >= (WIN_WIDTH - texture->getFrameWidth() - velocityX) || game->GetDirection().getX() == -1 && pos.getX() <= 1) {
		game->CannotMove();
	}
}

SDL_Rect Alien::GetRect() const{

	SDL_Rect target;

	target.x = pos.getX();
	target.y = pos.getY();
	target.w = texture->getFrameWidth();
	target.h = texture->getFrameHeight();

	return target;
}

void Alien::Shoot() {


	if (currenttime >= shootingtime) {
		game->FireLaser(Vector2D<>((pos.getX() + texture->getFrameWidth() / 2), pos.getY()), true);
		currenttime = 0;
		shootingtime = game->getRandomRange(MIN_TIME, MAX_TIME);

	}
}