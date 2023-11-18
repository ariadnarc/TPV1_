#include "checkML.h"
#include "Dog.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Texture.h"
using namespace std;


void Dog::render() const{

	SDL_Rect dogDestRect;
	dogDestRect.w = w;
	dogDestRect.h = h;
	dogDestRect.x = x;
	dogDestRect.y =y;

	texture->render(dogDestRect, SDL_FLIP_NONE);

}

void Dog::update() {
	x = (x + 10) % winWidth;
}

void Dog::handleEvents(SDL_Event& event) {

	bool exit = false;
	SDL_Event evento;
	/*
	while (SDL_PollEvent(&evento)) {
		
	}
	aqui va lo de pulsar una tecla y que haga lo que sea
	*/
}