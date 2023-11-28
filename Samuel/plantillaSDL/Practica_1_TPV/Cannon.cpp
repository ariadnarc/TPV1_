#include "checkML.h"


#include <iostream>
#include "SDL.h"
#include "Cannon.h"
#include "Game.h"

//constructor por parametros
Cannon::Cannon(Game* game, Texture* text, Point2D<> pos, int lifes)
	: SceneObject(game, pos, 0, 0, lifes), texture(text), direction(0, 0) {};


//constructor por lectura de archivo
Cannon::Cannon(Game* game, Texture* text, std::istream& in) 
	: SceneObject(game,in), texture(text) {
	
	in >> lifesLeft >> shootReload;	
	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
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
	if (waitingFrames <= 0 ) {
		Move();
		Shoot();

		waitingFrames = _frameRate;
	}

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

bool Cannon::Hit(SDL_Rect rect, char tLaser) {
	
	if (lifesLeft <= 0) return false;

	bool colision = false;

	SDL_Rect aux = getRect();

	if (tLaser == 'r') {
		if (SDL_HasIntersection(&rect, &aux)){
			colision = true;
			lifesLeft--;
			game->UpdateLifesUI();

			if (lifesLeft <= 0) {
				game->HasDied(iterator);
				game->playerDied();
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

		//sacar la posicion a un metodo spawnPoint
		game->fireLaser(Vector2D<>(	pos.getX() + texture->getFrameWidth()/2,
									pos.getY() - texture->getFrameHeight()/2), 
									'b');
	}
}






