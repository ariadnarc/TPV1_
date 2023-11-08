#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


using namespace std;

using uint = unsigned int;


SDL_Texture* CreateTexture(SDL_Renderer*& renderer ,const string& file) {
	SDL_Surface* surface;
	surface = IMG_Load(file.c_str());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}

void HandleEvents(SDL_Event& evento,bool& exit) {
	//carga los eventos 
	while (SDL_PollEvent(&evento) && !exit) {
		//trata los eventos en funcion de su tipo
		if (evento.type == SDL_QUIT)
			exit = true;
		else {


		}
	}
}

void Update() {

}


void main_ejercicio_1()
{
	//inicializar el window y el renderer
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	//tamaños de la ventana
	constexpr uint winWidth = 800;
	constexpr uint winHeight = 600;

	//inicializar sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//crear la ventana
	window = SDL_CreateWindow("First test with SDL", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	//crear el renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//si ha fallado la carga salir, sino codigo del programa
	if (window == nullptr || renderer == nullptr)
		cout << "Error cargando SDL" << endl;
	else {
		//codigo en sí del programa
		// 
		// no hace falta esto
		//SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

		SDL_RenderClear(renderer);

		SDL_Texture* textureDog; SDL_Texture* textureBackground; SDL_Texture* textureHelicopter;
		//ruta de las imagenes
		string dogFile = "../images/dog.png";
		string backGroundFile = "../images/background1.png";
		string helicopterFile = "../images/helicopter.png";

		//cargar textura perro
		textureDog = CreateTexture(renderer, dogFile);

		//cargar textura background
		textureBackground = CreateTexture(renderer, backGroundFile);

		//cargar textura helicoptero
		textureHelicopter = CreateTexture(renderer, helicopterFile);

		int dogW, dogH;
		int dogVelocity = 25;

		SDL_QueryTexture(textureDog, nullptr, nullptr, &dogW, &dogH);

		//rectangulo de origen perro
		SDL_Rect OriginRectDog;
		OriginRectDog.x = 0;
		OriginRectDog.y = 0;
		OriginRectDog.w = dogW/6;
		OriginRectDog.h = dogH;

		//rectangulo de destino perro
		SDL_Rect DestinyRectDog;
		DestinyRectDog.x = 0;
		DestinyRectDog.y = 400;
		DestinyRectDog.w = 100;
		DestinyRectDog.h = 100;



		int heliW, heliH;
		int heliVelocity = 40;

		SDL_QueryTexture(textureHelicopter, nullptr, nullptr, &heliW, &heliH);

		//rectangulo origen helicoptero
		SDL_Rect OriginRectHelicopter;
		OriginRectHelicopter.x = 0;
		OriginRectHelicopter.y = 0;
		OriginRectHelicopter.w = heliW/5;
		OriginRectHelicopter.h = heliH;

		//rectangulo destino helicoptero
		SDL_Rect DestinyRectHelicopter;
		DestinyRectHelicopter.x = 0;
		DestinyRectHelicopter.y = 50;
		DestinyRectHelicopter.w = heliW / 5;
		DestinyRectHelicopter.h = heliH;


		SDL_Event evento;
		bool exit = false;

		uint frameTime = 0;
		uint startTime = SDL_GetTicks();

		const uint FRAME_RATE = 250;

		


		while (!exit) {
			//tratar eventos
			HandleEvents(evento,exit);

			//actualizar el tiempo de frame
			frameTime = SDL_GetTicks() - startTime;

			//si va a pasar un frame
			if (frameTime >= FRAME_RATE) {
					
				//renderizado

				//clear de la pantalla, no se si ponerlo
				//SDL_RenderClear(renderer);
				//render texturas
				SDL_RenderCopy(renderer, textureBackground, nullptr, nullptr);
				SDL_RenderCopy(renderer, textureDog, &OriginRectDog, &DestinyRectDog);
				SDL_RenderCopyEx(renderer, textureHelicopter, &OriginRectHelicopter, &DestinyRectHelicopter,-20,nullptr, SDL_FLIP_NONE);
				
				//renderizar todo la cola
				SDL_RenderPresent(renderer);

				//update de datos para mover el sitio del perro y para cambiar su animacion
				DestinyRectDog.x = (DestinyRectDog.x + dogVelocity) % winWidth;
				OriginRectDog.x = (OriginRectDog.x + (dogW/6)) % (dogW-(dogW/6));

				DestinyRectHelicopter.x = (DestinyRectHelicopter.x + (winWidth - heliVelocity)) % winWidth;
				OriginRectHelicopter.x = (OriginRectHelicopter.x + (heliW / 5)) % (heliW - (heliW / 5));

				//actualizar el startTime para tiempo de frames
				startTime = SDL_GetTicks();
			}
		}
		

		//borrar texturas
		SDL_DestroyTexture(textureDog);
		SDL_DestroyTexture(textureBackground);


		//SDL_RenderPresent(renderer);
		//SDL_Delay(1100);
	}

	//destructores(renderer window, y sdl quit)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	main_ejercicio_1();


	return 0;
}

