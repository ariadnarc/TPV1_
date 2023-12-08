#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "Button.h"


Button::Button(GameState* game,Texture* texture,Point2D<> pos) 
	: GameObject(game),texture(texture),pos(pos) {

	height = texture->getFrameHeight();
	width = texture->getFrameWidth();

}

void Button::connect(Callback c) {
	callbackList.push_back(c); 
}


void Button::handleEvent(const SDL_Event& ev) {

	//ver si se ha pulsado el boton del raton y si el raton está encima del boton,
	//si se ha pulsado llamar a todos los callbacks de la lista
}

//llama a todas las funciones asociadas al boton
void Button::emit()const {

	for (Callback cb : callbackList) {
		cb();
	}
}

void Button::Render() const {
	SDL_Rect rect{pos.getX(),pos.getY(),width,height };
	texture->render();
}