#include "checkML.h"
#include "SDL.h"
#include "Game.h"
#include "Cannon.h"
#include <iostream>

void Cannon::Render()const {

	texture->render(GetRect());
}

bool Cannon::Update() {

	Move();

	Shoot();

	currentTime++;

	return lifesLeft > 0;
}

void Cannon::HandleEvents(SDL_Event ev) {
	
	SDL_Scancode code = ev.key.keysym.scancode;

	if (ev.type == SDL_KEYDOWN) {
		if (code == SDL_SCANCODE_A) {
			izqda = true;
		}
		else if (code == SDL_SCANCODE_D) {
			dcha = true;
		}
		else if (code == SDL_SCANCODE_SPACE) {
			espacio = true;
		}
	}
	else if (ev.type == SDL_KEYUP) {
		if (code == SDL_SCANCODE_A) {
			izqda = false;
		}
		else if (code == SDL_SCANCODE_D) {
			dcha = false;
		}
		else if (code == SDL_SCANCODE_SPACE) {
			espacio = false;
		}
	}
}

void Cannon::Hit() {
	lifesLeft--;
	game->updateLifes();
}

void Cannon::Move() {
	

	if (izqda == dcha) { //si se están pulsando las dos teclas A y D a la vez
		direction = Vector2D<>(0, 0); //no se mueve
	}
	else if (dcha != izqda) { // si sólo hay una de las dos pulsadas
		if (dcha) { //tecla D

			direction = Vector2D<>(1, 0); // se mueve a la derecha
		}
		else if (izqda) { //tecla A

			direction = Vector2D<>(-1, 0); // se mueve a la izquierda
		}
	}

	// si está en posición válida para moverse
	if (direction.getX() == 1 && pos.getX() <= (WIN_WIDTH - texture->getFrameWidth() - velocity) || 
		direction.getX() == -1 && pos.getX() >= 1) {

		pos = pos + direction * velocity; 
	}
	
}

void Cannon::Shoot() {
	if (espacio && currentTime > shootingTime) {
		game->FireLaser(Vector2D<>((pos.getX() + texture->getFrameWidth() / 2), pos.getY()), false);
		currentTime = 0;
	}
}

SDL_Rect Cannon::GetRect() const {

	SDL_Rect target;

	target.x = pos.getX();
	target.y = pos.getY();
	target.w = texture->getFrameWidth();
	target.h = texture->getFrameHeight();

	return target;
}

int Cannon::GetLifes() {
	return lifesLeft;
}