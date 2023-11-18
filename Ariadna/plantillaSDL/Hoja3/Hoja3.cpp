#include "checkML.h"
#include "Game.h"
#include "Dog.h"
#include "Texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

using uint = unsigned int;

/*
	void firstTest()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	constexpr uint winWidth = 800;
	constexpr uint winHeight = 600;

	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		SDL_Surface* surface;
		SDL_Texture* textureDog;
		SDL_Texture* textureBackground;

		string filename = "../images/dog.png";
		string filename2 = "../images/background1.png";

		//cargar textura del perro
		surface = IMG_Load(filename.c_str());
		textureDog = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		//cargar textura del fondo
		surface = IMG_Load(filename2.c_str());
		textureBackground = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		//
		//int widthDog, heightDog;
		//SDL_QueryTexture(textureDog, nullptr, nullptr, &widthDog, &heightDog);


		SDL_Rect dogOriginRect;
		dogOriginRect.x = 0; dogOriginRect.y = 0;


		SDL_QueryTexture(textureDog, nullptr, nullptr, &dogOriginRect.w, &dogOriginRect.h);

		dogOriginRect.w /= 6;

		SDL_Rect dogPlacementRect;
		dogPlacementRect.w = dogOriginRect.w;
		dogPlacementRect.h = dogOriginRect.h;
		dogPlacementRect.x = 0; dogPlacementRect.y = 400;
		bool exit = false;
		SDL_Event evento;

		//control del tiempo
		const uint FRAME_RATE = 100;
		uint startTime = SDL_GetTicks();
		uint frameTime;

		const int DOG_FRAMES = 6;
		int dogCurrentFrame = 0;

		while (!exit) {
			//handle events
			while (SDL_PollEvent(&evento)) {
				if (evento.type == SDL_QUIT)
					exit = true;
				else {
					
				}
			}

			frameTime = SDL_GetTicks() - startTime;
			if (frameTime >= FRAME_RATE) {

				dogCurrentFrame = (dogCurrentFrame + 1) % DOG_FRAMES;

				dogOriginRect.x = dogOriginRect.w * dogCurrentFrame;

				//update

				dogPlacementRect.x = (dogPlacementRect.x + 10) % winWidth;


				startTime = SDL_GetTicks();
			}

			//renderizado
			SDL_RenderCopy(renderer, textureBackground, nullptr, nullptr);
			SDL_RenderCopy(renderer, textureDog, &dogOriginRect, &dogPlacementRect);

			SDL_RenderPresent(renderer);
		}
		//SDL_DestroyTexture()
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
*/

int main(int argc, char* argv[])
{
	Game game;
	game.run();
	return 0;
}
