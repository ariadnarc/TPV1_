#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "Ufo.h"
#include "PlayState.h"


//constructor por parametros, sin terminar
Ufo::Ufo(PlayState* game, Point2D<> pos)
	:SceneObject(game, pos, 0, 0, 1) {};


//constructor por lectura de archivo
Ufo::Ufo(PlayState* game,Texture* texture, std::istream& in)
	:SceneObject(game, in),texture(texture) {

	//leer estado y espera
	int aux;
	in >> aux >> waitingFrames;
		
	currentState = (state)aux;

	if (currentState == left || currentState == right) {
		//setear la direccion segun el estado, solo afecta a la X
		dir = Vector2D<>(currentState == left ? -1 : 1, 0);
	}

	width = texture->getFrameWidth();
	height = texture->getFrameHeight();
}



void Ufo::Render() const {
	//si esta oculto no se renderiza
	if (currentState == hiddenLeft || currentState == hiddenRight) return;

	//si esta visible renderizar frame segun este destruido o no
	texture->renderFrame(getRect(), 0, currentState == destroyed ? 1 : 0);
}


void Ufo::Update() {


	//si esta oculto esperar hasta volver a salir
	if (currentState == hiddenLeft || currentState == hiddenRight) {
		--waitingFrames;

		//si ya le toca salir
		if (waitingFrames <= 0) {
			//siguiente  estado
			currentState = (state)(((int)currentState + 1) % 4);
			//setear la direccion segun el estado, solo afecta a la X
			dir = Vector2D<>(currentState == left ? -1 : 1,  0 );

			//setear la posicion
			pos = Point2D<>(currentState == right ? 0 : winWidth, pos.getY());

			waitingFrames = moveWaitingTime;
		}
	}
	else if (currentState != destroyed) { //si esta visible, moverse

		waitingFrames--;

		if (waitingFrames <= 0) {
			//movimiento horizontal solo
			pos = pos +  dir * velocityX;

			waitingFrames = moveWaitingTime;

			//si se sale de la pantalla, siguiente estado y actualizar el waitingFrames
			if (pos.getX() < (0 - width) || pos.getX() > winWidth) {
				//siguiente  estado
				currentState = (state)(((int)currentState + 1) % 4);

				waitingFrames = playState->getRandomRange(minWaitingTime, maxWaitingTime);
			}

		}

	}
	else {//destroyed
		waitingFrames--;

		if (waitingFrames <= 0) {
			playState->HasDied(sceneAnchor);
		}
	}
}

bool Ufo::Hit(SDL_Rect rect, char color) {

	//si no esta en ninguno de estos 2 estados no hay colision
	if(currentState != left && currentState != right) return false;
	

	SDL_Rect aux = getRect();

	//si es un laser del player y hay colision
	if (color == 'b' && SDL_HasIntersection(&rect, &aux)) {
		currentState = destroyed;
		waitingFrames = destroyedWaitingTime;
		playState->UfoDied();
		return true;
	}
	else return false;
}

void Ufo::Save(std::ostream& out) const{

	out << UFO_TYPE << " ";

	SceneObject::Save(out);

	out << currentState << " " << waitingFrames << " ";

	out << '\n';

}


