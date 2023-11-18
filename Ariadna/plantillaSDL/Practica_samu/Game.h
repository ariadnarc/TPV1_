#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <vector>
#include<random>

#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"
#include "Alien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"

#include "InfoBar.h"

#include "checkML.h"


//a lo mejor no va aquí
struct TextureInfo {
	std::string fileName;
	int horizontalFrames, verticalFrames;

	TextureInfo(std::string fname, int hframes, int vframes)
		: fileName(fname), horizontalFrames(hframes), verticalFrames(vframes) {};
};

	
using uint = unsigned int;


//DECLARACION DE CONSTANTES

//tamaños de la ventana
constexpr uint winWidth = 800;
constexpr uint winHeight = 600;

//frame rate
constexpr uint FRAME_RATE = 100;

constexpr uint NUM_TEXTURAS = 4;

const std::string TEXTURE_ROOT = "../Practica1TPV/images/";

//enumerado texturas
enum TextureName{ALIENS,BUNKER,SPACESHIP,STARS};


//CONSTANTES DE JUEGO
constexpr int PLAYER_LIFES = 3;
constexpr int BUNKER_LIFES = 10;


class Game {

	//VARIABLES DE SDL
	SDL_Window* window;
	SDL_Renderer* renderer;

	//ARRAY DE TEXTURAS
	Texture* arrayTexturas[NUM_TEXTURAS];
	

	//OBJETOS DEL JUEGO	 
	std::vector<Bunker*> bunkers;
	std::vector<Alien*> aliens;
	std::vector<Laser*> lasers;

	Cannon* player;

	//CICLO DE JUEGO
	bool exit = false;

	uint frameTime = 0;
	uint startTime;
	
	//MOVIMIENTO DE LOS ALIENS
	Vector2D<> aliensDirection;
	bool cannotM = false;
	bool goDown = false;
	int nextDirX = 0;


	//GENERADOR ALEATORIO
	std::mt19937_64 randomGenerator;

	//numero aleatorio de disparadores y tipos aleatorios de aliens
	const bool randomMode = true;
	const int shootersPercent = 80;

	//barra de informacion
	InfoBar* infoB;

	//puntuacion
	int score = 0;


	//bucle de juego
	void Render()const;
	void Update();
	void HandleEvents();


	//carga de objetos
	void ReadMap(const std::string mapPath);

	//metodos privados auxiliares
	
	//inicializa SDL, las variables window y renderer y maneja los posibles errores correspondientes
	void InitializeSDL();
	//carga las texturas del juego
	void LoadTextures(const std::vector<TextureInfo>& textInfo);
	//inicializa el randomMode, a lo mejor esto hay que cambiarlo
	void RandomMode();
	//carga la musica de fondo del juego
	void LoadMusic();

public:
	void Run();

	//obtener la direccion de movimiento de los alienigenas
	Vector2D<> getDirection() const { return aliensDirection; }// cambiar por Vector2D

	//devuelve el renderer
	SDL_Renderer* getRenderer() const { return renderer; }

	//devuelve el ancho de ventana
	int getWinWidht()const { return winWidth; }

	//informar de que no es posible moverse otra iteración más en la dirección actual
	void cannotMove();
	
	//disparar laser
	void fireLaser(Vector2D<> pos,bool originA);

	//hace el calculo de colisiones
	bool collisions(const Laser* laser);

	//devuelve un numero aleatorio con distrubucion uniforme en el rango dado
	int getRandomRange(int min, int max);

	//los aliens la llaman cuando llegan al umbral inferior de la pantalla
	void aliensLimitBotton();

	void UpdateLifesUI();


	//constructor
	Game(const std::vector<TextureInfo>& texturesInfo);
	//destructor
	~Game();
};






#endif // !GAME_H_

