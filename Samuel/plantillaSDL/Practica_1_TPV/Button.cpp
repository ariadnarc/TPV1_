#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "Button.h"


Button::Button(GameState* game,Texture* texture,Point2D<> pos) 
	: GameObject(game),texture(texture),pos(pos) {

	height = texture->getFrameHeight();
	width = texture->getFrameWidth();

	myRect =  SDL_Rect{(int)pos.getX(), (int)pos.getY(), width, height };

}

void Button::connect(Callback c) {
	callbackList.push_back(c); 
}


void Button::handleEvent(const SDL_Event& ev) {

	//ver si se ha pulsado el boton del raton y si el raton est� encima del boton,
	//si se ha pulsado llamar a todos los callbacks de la lista
	if (ev.type == SDL_MOUSEBUTTONDOWN &&
		ev.button.button == SDL_BUTTON_LEFT) {
		
		// Posici�n del rat�n cuando se puls�
		SDL_Point point{ ev.button.x, ev.button.y };


		if (SDL_PointInRect(&point, &myRect)) {
			emit();
		}
	}
}

//llama a todas las funciones asociadas al boton
void Button::emit()const {

	for (Callback cb : callbackList) {
		cb();
	}
}

void Button::Render() const {
	texture->render(myRect);
}

void Button::Update(){

	SDL_Point point;
	SDL_GetMouseState(&point.x, &point.y);

	// Comprueba si el rat�n est� sobre el rect�ngulo
	hover = SDL_PointInRect(&point, &myRect);
}