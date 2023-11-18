#pragma once

#include "Texture.h"
#include "Dog.h"
#include "SDL.h"
#include <iostream>

using uint = unsigned int;

constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;
constexpr uint NUM_TEXTURES = 3;

class Game {
private:

	SDL_Rect windowRect;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture* arrayText[NUM_TEXTURES];

	Dog* sally;
	//Helicopter* helicopter;

	//control del tiempo
	const uint FRAME_RATE = 100;

	uint startTime;
	uint frameTime;

	bool exit = false;

public:
	Game();
	~Game();
	void run();
	void render() const;
	void handleEvents();
	void update();
};

