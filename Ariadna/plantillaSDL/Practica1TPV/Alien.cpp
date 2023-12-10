#include "checkML.h"
#include "SDL.h"
#include "Game.h"
#include <iostream>
#include "Alien.h"


//constructor por parametros
Alien::Alien(PlayState* game, Texture* text, Mothership* mother, Point2D<> _pos, int _type)
	: SceneObject(game, _pos, 0, 0, 1), texture(text), type(_type), animFrame(0), mother(mother) {

	mother->addAlien();
};

//constructor por lectura de archivo
Alien::Alien(PlayState* game, Texture* text, Mothership* mother, std::istream& in)
	: SceneObject(game, in), texture(text), mother(mother), animFrame(0) {
	in >> type;
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
	mother->addAlien();

}

void Alien::Save(std::ostream& out) const {
	//pasar el magic number a un enumerado
	if (getType() != 0) out << ALIEN << " ";

	SceneObject::Save(out);

	out << type << " ";

	if (getType() != 0) out << '\n';

}



void Alien::Render() const {
	texture->renderFrame(getRect(), type, animFrame);
}

void Alien::UpdateAnim() {
	animFrame = (animFrame + 1) % texture->getNumColumns();
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
			if (lifesLeft <= 0) {
				playState->HasDied(sceneAnchor);
				mother->alienDied();
				playState->AlienDied(type);
			}
			//falta llamar al motherShip para disminuir el numero de aliens
		}
	}


	return colision;

}


void Alien::Move() {
	Vector2D<> dir = mother->getDirection();

	//pos = Vector2D<>(pos.getX() +  (dir.getX() * mother->getVelocityX()),
	//				 pos.getY() +  (dir.getY() * mother->getVelocityY()) );

	//otra version del move
	pos = pos + (Vector2D<>(mother->getVelocityX() * dir.getX(),
		mother->getVelocityY() * dir.getY()));

	if (
		(dir.getX() == -1 &&
			pos.getX() <= (0 + mother->getVelocityX())) ||

		(dir.getX() == 1 &&
			pos.getX() >= (winWidth - (texture->getFrameWidth()) - mother->getVelocityX()))
		)
	{
		mother->cannotMove();
	}


	if (pos.getY() >= ALIENS_LIMIT_Y) {
		mother->alienLanded();
	}

}