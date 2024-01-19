#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include<gl/GLU.h>
#include <gl/GL.h>

int main(int argc, char* argv[]) {

	SDL_Window* window;
	SDL_Renderer* renderer;

	int winWidth = 600;
	int winHeight = 600;

	//inicializar sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//crear la ventana
	window = SDL_CreateWindow("Practica 1 TPV", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	//crear el renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//si ha fallado la carga salir, sino codigo del programa
	if (window == nullptr || renderer == nullptr)
		throw "error";


	bool exit = false;
	SDL_Event evento;

	unsigned int startTime;
	unsigned int frameTime;

	int FRAME_RATE = 20;

	SDL_GL_CreateContext(window);

	//version suspendiendo el programa,consume menos recursos	
	while (!exit) {
		//actualizar el start time
		startTime = SDL_GetTicks();


		//carga los eventos 
		while (SDL_PollEvent(&evento) && !exit) {
			//trata los eventos en funcion de su tipo()
			if (evento.type == SDL_QUIT) {

				exit = true;
			}
			else {
			}
		}
		

		//calcular el tiempo de frame
		frameTime = SDL_GetTicks() - startTime;

		//prueba para ver cuanto tardan los frames
		//std::cout << frameTime << std::endl;

		//si queda tiempo de frame, suspender el programa el tiempo que queda
		if (frameTime < FRAME_RATE) {

			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
	



	return 0;
}
