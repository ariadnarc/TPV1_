#ifndef Game_H_
#define Game_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "texture.h"
#include "GameStateMachine.h"
#include "InvadersError.h"



//struct para informacion de las texturas
struct TextureInfo {
	std::string fileName;
	int horizontalFrames, verticalFrames;

	TextureInfo(std::string fname, int nRows, int nColums)
		: fileName(fname), horizontalFrames(nRows), verticalFrames(nColums) {};
};

using uint = unsigned int;

//numero de texturas
constexpr uint NUM_TEXTURAS = 6;
//ruta comun  de  las texturas
const std::string TEXTURE_ROOT = "images/";

//enumerado texturas
enum TextureName { ALIENS, BUNKER, SPACESHIP, STARS, FONT, UFO };


//DECLARACION DE CONSTANTES

//tamaños de la ventana
constexpr uint winWidth = 800;
constexpr uint winHeight = 600;

//frame rate
constexpr uint FRAME_RATE = 20;

class Game {

	//VARIABLES DE SDL
	SDL_Window* window;
	SDL_Renderer* renderer;

	//ARRAY DE TEXTURAS
	Texture* arrayTexturas[NUM_TEXTURAS];

	GameStateMachine* gameStateMachine;

	//CICLO DE JUEGO
	bool exit = false;

	uint frameTime = 0;
	uint startTime;


	void Render() const;
	void Update();
	void HandleEvents();


	//inicializa SDL, las variables window y renderer y maneja los posibles errores correspondientes
	void InitializeSDL();

	//carga las texturas del juego
	void LoadTextures();
	

public: 

	//constructor
	Game();

	//destructor
	~Game();

	Texture* getTexture(TextureName name) const { return arrayTexturas[name]; }

	void RenderClear() const { SDL_RenderClear(renderer); }

	SDL_Renderer* getRenderer() { return renderer; }

	void Run();

};



#endif // !Game_H_

