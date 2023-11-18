#pragma once

#include "Texture.h"
#include "SDL.h"
#include <iostream>

using uint = unsigned int;

class Dog {
private:
	uint winWidth = 800;
	uint w = 0; // width
	uint h = 0; // height
	uint x = 0; uint y = 0; // Posición de esquina superior izqda
	int dirX = 0; int dirY = 0; // Dirección de movimiento
	Texture* texture = nullptr;

public:
	Dog() {};
	Dog(uint w, uint h, uint x, uint y, Texture* t) :
		w(w), h(h), x(x), y(y), texture(t) {}
	~Dog() {}
	void render() const;
	void update();
	void handleEvents(SDL_Event& event);

};

