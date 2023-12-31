#include "checkML.h"
#include "SDL.h"
#include "Game.h"
#include "Cannon.h"
#include <iostream>

//constructor por parametros
Cannon::Cannon(PlayState* game, Texture* text, Point2D<> pos, int lifes)
	: SceneObject(game, pos, 0, 0, lifes), texture(text), direction(0, 0) {

	playState->addEventListener(this);

};


//constructor por lectura de archivo
Cannon::Cannon(PlayState* game, Texture* text, std::istream& in)
	: SceneObject(game, in), texture(text) {

	in >> lifesLeft >> shootReload;
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();

	playState->addEventListener(this);
}

void Cannon::Save(std::ostream& out) const {
	out << CANNON << " ";
	//save del SceneObject
	SceneObject::Save(out);

	out << lifesLeft << " " << waitingFrames << " ";

	out << '\n';
}


void Cannon::Render()const {
	texture->render(getRect());
}

void Cannon::Update() {

	if (lifesLeft <= 0) return;

	--waitingFrames;
	if (waitingFrames <= 0) {
		Move();
		Shoot();

		waitingFrames = _frameRate;
	}

}


void Cannon::handleEvent(const SDL_Event& ev) {

	SDL_Scancode code = ev.key.keysym.scancode;

	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code == SDL_SCANCODE_A)		leftWASD = true;
		else if (code == SDL_SCANCODE_D)		rightWASD = true;
		else if (code == SDL_SCANCODE_LEFT)		leftArrow = true;
		else if (code == SDL_SCANCODE_RIGHT)	rightArrow = true;
		else if (code == SDL_SCANCODE_SPACE)	space = true;
	}
	else if (ev.type == SDL_KEYUP) {
		if (code == SDL_SCANCODE_A)		leftWASD = false;
		else if (code == SDL_SCANCODE_D)		rightWASD = false;
		else if (code == SDL_SCANCODE_LEFT)		leftArrow = false;
		else if (code == SDL_SCANCODE_RIGHT)	rightArrow = false;
		else if (code == SDL_SCANCODE_SPACE)	space = false;
	}
}

bool Cannon::Hit(SDL_Rect rect, char tLaser) {

	if (lifesLeft <= 0) return false;

	bool colision = false;

	SDL_Rect aux = getRect();

	if (tLaser == 'r') {
		if (SDL_HasIntersection(&rect, &aux)) {
			colision = true;
			lifesLeft--;
			playState->UpdateLifesUI();

			if (lifesLeft <= 0) {
				playState->HasDied(sceneAnchor);
				playState->playerDied();
			}

		}
	}


	return colision;
}

void Cannon::Move() {

	bool left = leftWASD || leftArrow;
	bool right = rightWASD || rightArrow;
	//asignar la direccion de movimiento en funcion del input
	direction = left == right ? Vector2D<>(0, 0) : left ? Vector2D<>(-1, 0) : Vector2D<>(1, 0);

	//movimiento limitado con los bordes de la pantalla
	if ((direction.getX() == -1 && pos.getX() >= 0 + velocity) ||
		(direction.getX() == 1 && pos.getX() < (winWidth - texture->getFrameWidth()) - velocity)) {
		pos = pos + direction * velocity;
	}
}

void Cannon::Shoot() {

	shootReload++;

	if (space && shootReload > SHOOT_RATE) {
		shootReload = 0;

		//sacar la posicion a un metodo spawnPoint
		playState->fireLaser(Vector2D<>(pos.getX() + texture->getFrameWidth() / 2,
			pos.getY() - texture->getFrameHeight() / 2),
			'b');
	}
}