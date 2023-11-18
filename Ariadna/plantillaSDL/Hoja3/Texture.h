#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using uint = unsigned int;

class Texture {
private:
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	uint w = 0; uint h = 0;
		uint fw = 0; uint fh = 0; // Frame widthand height
		uint numCols = 1; uint numRows = 1;
public:
	Texture(SDL_Renderer* r) : renderer(r) {};
	Texture(SDL_Renderer* r, std::string filename, uint numRows = 1, uint numCols = 1)
		: renderer(r) {
		load(filename, numRows, numCols);
	};
	~Texture() { Free(); };
	void Free();
	int getW() const { return w; };


	void load(std::string filename, uint numRows = 1, uint numCols = 1);
	void render(const SDL_Rect& rect, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
	void renderFrame(const SDL_Rect& destRect, int row, int col, int angle = 0,
		SDL_RendererFlip flip = SDL_FLIP_NONE) const;
};
