#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Dog.h"
#include "Texture.h"

#include "Game.h"


void PlayState::Render()const {

	//clear de la pantalla(si se va a repintar toda la pantalla opcional)
	//SDL_RenderClear(renderer);
	
	//render del background
	arrayTexturas[BACKGROUND] ->Render(nullptr, nullptr);

	dog->Render();
	helicopter->Render();

	//renderizar todo la cola
	SDL_RenderPresent(renderer);
}

void PlayState::Update() {

	dog->Update();
	helicopter->Update();

}

void PlayState::HandleEvents(){
	SDL_Event evento;

	//carga los eventos 
	while (SDL_PollEvent(&evento) && !exit) {
		//trata los eventos en funcion de su tipo()
		if (evento.type == SDL_QUIT)
			exit = true;
		else {
			dog->HandleEvents(evento);

		}
	}

}

void PlayState::Run() {

	/* 
	version control total pero consume mas recursos
	
	while (!exit) {
		HandleEvents();
		//actualizar el tiempo de frame
		frameTime = SDL_GetTicks() - startTime;

		//si va a pasar un frame
		if (frameTime >= FRAME_RATE) {
			Update();
			//actualizar el startTime para tiempo de frames
			startTime = SDL_GetTicks();
		}
		Render();
	}
	*/

	//version suspendiendo el programa,consume menos recursos
	while (!exit) {
		//actualizar el start time
		startTime = SDL_GetTicks();

		//ejecutar el bucle principal
		HandleEvents();
		Update();
		Render();

		//calcular el tiempo de frame
		frameTime = SDL_GetTicks() - startTime;

		//si queda tiempo de frame, suspender el programa el tiempo que queda
		if (frameTime < FRAME_RATE) {
			
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
}


//constructor
PlayState::PlayState(std::vector<std::string> texturesPath)
{
	//inicializar sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//crear la ventana
	window = SDL_CreateWindow("Ejercicio 3", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	//crear el renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//si ha fallado la carga salir, sino codigo del programa
	if (window == nullptr || renderer == nullptr)
		throw "Error loading SDL window or renderer";

	//crear las texturas
	arrayTexturas[DOG] = new Texture(renderer,texturesPath[0]); 
	arrayTexturas[BACKGROUND] = new Texture(renderer,texturesPath[1]); 
	arrayTexturas[HELICOPTER] = new Texture(renderer,texturesPath[2]); 


	int dogScale, helicopterScale;
	dogScale = helicopterScale = 1;

	int dogFrames = 6;
	int helicopterFrames = 5;


	//inicializar los objetos
	dog = new Dog(arrayTexturas[DOG],dogFrames,dogScale,winWidth);
	helicopter = new Helicopter(arrayTexturas[HELICOPTER],helicopterFrames,helicopterScale,winWidth);


	dog->SetPosition(0, 400);

	helicopter->SetPosition(0, 100);


	//inicializar valores de los objetos
	dog->setVelocity(20);
	helicopter->setVelocity(30);

	//inicializar el contador de tiempo
	startTime = SDL_GetTicks();
};

//destructor
PlayState::~PlayState() {
	//delete de las texturas(dentro se hace el SDL_DestroyTexture)
	for (int i = 0; i < 3; i++) {
		delete arrayTexturas[i];
	}

	//delete de los objetos(eran punteros)
	delete dog;
	delete helicopter;

	//destructores(renderer window, y sdl quit)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}