#ifndef GAME_H_
#define GAME_H_

#include "checkML.h"


#include <iostream>
#include <vector>
#include <random>
#include <string> //para usar to string
#include <filesystem>

#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"

#include "Alien.h"
#include "ShooterAlien.h"
#include "Bunker.h"
#include "Cannon.h"
#include "Laser.h"
#include "Ufo.h"

#include "InfoBar.h"



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

constexpr uint NUM_TEXTURAS = 6;


const std::string TEXTURE_ROOT = "images/";

//enumerado texturas
enum TextureName{ALIENS,BUNKER,SPACESHIP,STARS,FONT,UFO};

//enumerado tipos de objetos

enum ObjectTypes{CANNON,ALIEN,SHOOTER_ALIEN,MOTHERSHIP,BUNKER_TYPE,UFO_TYPE,LASER};

//ruta del mapa
const std::string MAP_PATH = "mapas/original.txt";

//puntuaciones de los aliens

const int SCORE_ALIENS[] = { 30,20,10 };

const int SCORE_UFO = 100;

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
	std::list<SceneObject*> objects;

	std::vector<std::list<SceneObject*>::iterator> iteratorsDied;

	Cannon* player;

	Mothership* mother;
	


	//CICLO DE JUEGO
	bool exit = false;

	uint frameTime = 0;
	uint startTime;



	//GENERADOR ALEATORIO
	std::mt19937_64 randomGenerator;

	//numero aleatorio de disparadores y tipos aleatorios de aliens
	const bool randomMode = false;
	const int shootersPercent = 60;

	//barra de informacion
	InfoBar* infoB;

	//puntuacion
	int score = 0;

	//audio,sacar a una clase
	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_AudioDeviceID deviceId;

	//guardado de partidas
	bool saving = false;
	bool loading = false;

	int currentInputFrames = 0;//buscar un mejor nombre
	int maxInputFrames = 100;

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
	void LoadGame(std::string savePath);

public:
	void Run();

	//devuelve el renderer
	SDL_Renderer* getRenderer() const { return renderer; }

	//devuelve el ancho de ventana
	int getWinWidht()const { return winWidth; }
	
	//disparar laser
	void fireLaser(Vector2D<> pos,char color);

	//hace el calculo de colisiones
	bool collisions(const Laser* laser);

	//devuelve un numero aleatorio con distrubucion uniforme en el rango dado
	int getRandomRange(int min, int max);

	//los aliens la llaman cuando llegan al umbral inferior de la pantalla
	void aliensLimitBotton();

	void UpdateLifesUI();

	void UpdateScoreUI();

	//esto a lo mejor hay que cambiarlo a una clase,para la carga de partidas con slots
	void ChoseSlot(SDL_Event ev);

	void TryLoad(SDL_Event ev);

	//el iterador va por referencia?
	void HasDied(std::list<SceneObject*>::iterator it);


	void AlienDied(int type);

	void UfoDied();
	//constructor
	Game(const std::vector<TextureInfo>& texturesInfo);
	//destructor
	~Game();
};






#endif // !GAME_H_

