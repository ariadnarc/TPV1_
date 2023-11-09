#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <vector>
#include <random>

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

	TextureInfo(std::string fname, int nRows, int nColums)
		: fileName(fname), horizontalFrames(nRows), verticalFrames(nColums) {};
};

	
using uint = unsigned int;


//DECLARACION DE CONSTANTES

//tamaños de la ventana
constexpr uint winWidth = 800;
constexpr uint winHeight = 600;

//frame rate
constexpr uint FRAME_RATE = 20;

constexpr uint NUM_TEXTURAS = 5;


const std::string TEXTURE_ROOT = "images/";

//enumerado texturas
enum TextureName{ALIENS,BUNKER,SPACESHIP,STARS,FONT};

//ruta del mapa
const std::string MAP_PATH = "mapas/original.txt";

//puntuaciones de los aliens

const int SCR_ALIEN_TYPE_0 = 10;
const int SCR_ALIEN_TYPE_1 = 10;
const int SCR_ALIEN_TYPE_2 = 10;

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
	bool _goDown = false;
	int nextDirX = 0;


	//GENERADOR ALEATORIO
	std::mt19937_64 randomGenerator;

	//numero aleatorio de disparadores y tipos aleatorios de aliens
	const bool randomMode = false;
	const int shootersPercent = 60;

	//barra de informacion
	InfoBar* infoB;

	//puntuacion
	int score = 0;

	//audio
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_AudioDeviceID deviceId;

	//para el incremento de velocidad de los aliens
	int scoreToIncreaseVelocity = 100;


	bool saving = false;
	int currentRenameFrames = 0;
	int savingRenameFrames = 100;

	int slotNumber;

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

	//guardar partida
	void SaveGame();

	//cargar partida
	void LoadGame();

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

	void goDown();
	
	//disparar laser
	void fireLaser(Vector2D<> pos,bool originA);

	//hace el calculo de colisiones
	bool collisions(const Laser* laser);

	//devuelve un numero aleatorio con distrubucion uniforme en el rango dado
	int getRandomRange(int min, int max);

	//los aliens la llaman cuando llegan al umbral inferior de la pantalla
	void aliensLimitBotton();

	void UpdateLifesUI();

	void UpdateScoreUI();

	//esto a lo mejor hay que cambiarlo a una clase,para la carga de partidas con slots
	void TryRename(SDL_Event ev);

	//constructor
	Game(const std::vector<TextureInfo>& texturesInfo);
	//destructor
	~Game();
};






#endif // !GAME_H_

