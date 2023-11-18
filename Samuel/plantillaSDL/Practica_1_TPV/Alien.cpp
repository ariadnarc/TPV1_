#include "checkML.h"


#include <iostream>
#include "SDL.h"
#include "Alien.h"
#include "Game.h"



int Alien::_moveFrameRate = 13;

//constructor por parametros
Alien::Alien(Game* game, Texture* text, Mothership* mother, Point2D<> _pos, int _type)
	: SceneObject(game, _pos, 0, 0, 1), texture(text), type(_type), frame(0), mother(mother) {};

//constructor por lectura de archivo
Alien::Alien(Game* game, Texture* text,Mothership* mother, std::istream& in) 
	: SceneObject(game,in),texture(text),mother(mother) {
	in >> type;
}

void Alien::Save(std::ostream& out) const {
	//pasar el magic number a un enumerado
	out << ALIEN << " ";

	SceneObject::Save(out);

	out << type << " ";

	out << '\n';

}



void Alien::Render() const {
	texture->renderFrame(getRect(), type, frame);
}

void Alien::UpdateAnim() {
	frame = (frame + 1) % texture->getNumColumns();
}

void Alien::Update() {

	if (lifesLeft <= 0) return;

	if (mother->shouldMove()) {
		UpdateAnim();
		Move();
	}
}

bool Alien::Hit(SDL_Rect rect, char tLaser) {

	if (lifesLeft <= 0) return false;


	bool colision = false;

	SDL_Rect aux = getRect();

	if (tLaser == 'b') {
		if (SDL_HasIntersection(&rect, &aux)) {
			colision = true;
			lifesLeft--;
			if (lifesLeft <= 0) game->HasDied(iterator);
			//falta llamar al motherShip para disminuir el numero de aliens
		}
	}


	return colision;

}


void Alien::Move() {
	Vector2D<> dir = mother->getDirection();
	
	pos = Vector2D<>(pos.getX() +  (dir.getX() * velocityX),
					 pos.getY() +  (dir.getY() * velocityY) );

	
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


