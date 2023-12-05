#ifndef Game_H_
#define Game_H_


#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Dog.h"
#include "Texture.h"
#include <vector>
#include "Helicopter.h"

using uint = unsigned int; 

//tamaños de la ventana
constexpr uint winWidth = 800;
constexpr uint winHeight = 600;

constexpr uint FRAME_RATE = 250;

constexpr uint NUM_TEXTURAS = 3;

enum Texturas { DOG, BACKGROUND, HELICOPTER };

class PlayState {
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	Texture* arrayTexturas[NUM_TEXTURAS];
	
	Dog* dog = nullptr;
	Helicopter* helicopter= nullptr;

	
	uint frameTime = 0;
	uint startTime;

	bool exit = false;

	void Render()const;
	void Update();
	void HandleEvents();

public:
	void Run();

	//constructor
	PlayState(std::vector<std::string> texturesPath);
	//destructor
	~PlayState();
};


#endif // !Game_H_

