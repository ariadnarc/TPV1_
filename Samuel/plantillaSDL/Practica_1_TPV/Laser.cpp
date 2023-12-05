#include "checkML.h"


#include <iostream>
#include "SDL.h"
#include "Laser.h"
#include "PlayState.h"


//constructor por parametros
Laser::Laser(PlayState* game, Point2D<> pos, char color)
	: SceneObject(game, pos, WIDTH, HEIGHT, 1), color(color){

	if (color == 'r') {
		velocityVector = Vector2D<>(0, 1);
		velocity = alienLaserVel;
	}
	else {
		velocityVector = Vector2D<>(0, -1);
		velocity = playerLaserVel;
	}

}
	
//constructor por lectura de archivos
Laser::Laser(PlayState* game, std::istream& in) 
	: SceneObject(game,in) {
	in >> color;

	//sacar a un metodo privado
	if (color == 'r') {
		velocityVector = Vector2D<>(0, 1);
		velocity = alienLaserVel;
	}
	else {
		velocityVector = Vector2D<>(0, -1);
		velocity = playerLaserVel;
	}

	width = WIDTH;
	height = HEIGHT;
}


void Laser::Save(std::ostream& out) const {

	out << LASER << " ";

	SceneObject::Save(out);

	out << color << " ";

	out << '\n';

}

void Laser::Render() const  {	
	SDL_Rect rect = getRect();

	SDL_SetRenderDrawColor(game->getRenderer(), color == 'r' ? 255 : 0, 0, color == 'r' ? 0 : 255, 255);
	SDL_RenderFillRect(game->getRenderer(), &rect);
}

void Laser::Move() {
	pos = pos + (velocityVector * velocity);
}

bool Laser::Colisions() {
	return playState->collisions(this);;
}

void Laser::Update() {

	if (lifesLeft <= 0) return;//para no hacer llamadas en un objeto muerto


	--waitingFrames;
	if (waitingFrames <= 0) {
		Move();

		waitingFrames = _frameRate;
	}

	if (Colisions() || pos.getY() < 0 || pos.getY() > winHeight) {
		playState->HasDied(sceneAnchor);
	}
}


bool Laser::Hit(SDL_Rect rect, char tLaser) {

	if (lifesLeft <= 0) return false;


	bool colision = false;

	SDL_Rect aux = getRect();


	if (tLaser != color) {
		if (SDL_HasIntersection(&rect, &aux)) {
			colision = true;
			lifesLeft--;
			if (lifesLeft <= 0) playState->HasDied(sceneAnchor);
			//falta logica pool de balas, llamar a otro metodo del game
		}
	}

	return colision;
}

