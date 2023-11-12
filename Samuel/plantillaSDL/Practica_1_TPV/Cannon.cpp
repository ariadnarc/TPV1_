#include <iostream>
#include "SDL.h"
#include "Cannon.h"
#include "Game.h"

#include "checkML.h"


void Cannon::Render()const {	
	texture->render(getRect());
}

void Cannon::Update() {
	
	_currentFrame++;
	if (_currentFrame >= _frameRate) {
		Move();
		Shoot();

		_currentFrame = 0;
	}

	//return lifesLeft > 0;
}


void Cannon::HandleEvents(SDL_Event ev) {

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

void Cannon::Hit(SDL_Rect rect, char tLaser) {
	//lifesLeft--;
	//game->UpdateLifesUI();
}

void Cannon::Move() {

	bool left = leftWASD || leftArrow;
	bool right = rightWASD || rightArrow;
	//asignar la direccion de movimiento en funcion del input
	direction = left == right ? Vector2D<>(0, 0) : left ? Vector2D<>(-1, 0) : Vector2D<>(1, 0);

	/*Alternativa, gestion de movimiento sin usar eventos, con el keyboardState
	const Uint8* pressed = SDL_GetKeyboardState(nullptr);
	int directionX = 0;

	if (pressed[SDL_SCANCODE_RIGHT] || pressed[SDL_SCANCODE_D])
		++directionX;

	if (pressed[SDL_SCANCODE_LEFT] || pressed[SDL_SCANCODE_A])
		--directionX;

	direction = Vector2D<>(directionX, 0);
	*/


	/* alternativa como la anterior pero usando booleanos
	const Uint8* pressed = SDL_GetKeyboardState(nullptr);

	bool left = pressed[SDL_SCANCODE_LEFT] || pressed[SDL_SCANCODE_A];
	bool right = pressed[SDL_SCANCODE_RIGHT] || pressed[SDL_SCANCODE_D];

	direction = left == right ? Vector2D<>(0, 0) : left ? Vector2D<>(-1, 0) : Vector2D<>(1, 0);
	*/


	//movimiento limitado con los bordes de la pantalla
	if ((direction.getX() == -1 && pos.getX() >= 0 + velocity) ||
		 (direction.getX() == 1  && pos.getX() < (game->getWinWidht() - texture->getFrameWidth()) - velocity )){
		pos = pos + direction*velocity;
	}
}

void Cannon::Shoot() {
	
	shootReload++;

	if (space && shootReload > SHOOT_RATE) {
		shootReload = 0;

		game->fireLaser(Vector2D<>(	pos.getX()+texture->getFrameWidth()/2,
									pos.getY()- texture->getFrameHeight()/2), 
									'b');
	}
}


SDL_Rect Cannon::getRect() const {
	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = texture->getFrameWidth();
	rect.h = texture->getFrameHeight();

	return rect;
}


void Cannon::Save(std::ostream& out) const {

}