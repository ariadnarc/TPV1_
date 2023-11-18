#include "checkML.h"
#include "Game.h"
#include "Dog.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

Game::Game() {

	SDL_Init(SDL_INIT_EVERYTHING);

	windowRect.w = WIN_WIDTH;
	windowRect.h = WIN_HEIGHT;

	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH,WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr) {

		cout << "Error cargando SDL" << endl;
	}
	else {

		arrayText[0] = new Texture(renderer, "../images/background1.png", 1, 1);
		arrayText[1] = new Texture(renderer, "../images/dog.png", 1, 1);
		arrayText[2] = new Texture(renderer, "../images/helicopter.png", 1, 1);
	

		sally = new Dog();
		//helicopter = new Helicopter();
	}
	
}
Game::~Game() {

	for (int i = 0;i < NUM_TEXTURES;i++) {
		delete arrayText[i];
	}

	delete sally;
	//delete helicopter;
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
void Game::run()
{
	while (!exit) {
		startTime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) {
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
} 
void Game::update() {
	sally->update();
	//helicopter->Update();
}
void Game::render() const
{
	SDL_RenderClear(renderer);

	arrayText[0]->render(windowRect, SDL_FLIP_NONE);
	sally->render();
	//helicopter->render();

	SDL_RenderPresent(renderer);
}
void Game::handleEvents()
{
	SDL_Event evento;

	while (SDL_PollEvent(&evento) && !exit) {

		if (evento.type == SDL_QUIT) {
			exit = true;
		}
		else {
			sally->handleEvents(evento);
			//helicopter->handleEvents(evento);
		}

	}
	
}
