#ifndef PlayState_H_
#define PlayState_H_

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
#include "Bomb.h"
#include "InfoBar.h"


#include "InvadersError.h"


#include "GameState.h"
#include "Game.h"
	
using uint = unsigned int;


//enumerado tipos de objetos
enum ObjectTypes{CANNON,ALIEN,SHOOTER_ALIEN,MOTHERSHIP,BUNKER_TYPE,UFO_TYPE,LASER};

//ruta del mapa
const std::string MAP_PATH = "mapas/original.txt";

//puntuaciones de los aliens y del  ufo

const int SCORE_ALIENS[] = { 30,20,10 };
const int SCORE_UFO = 100;

//CONSTANTES DE JUEGO
constexpr int PLAYER_LIFES = 3;
constexpr int BUNKER_LIFES = 10;



class PlayState : public GameState{

	//OBJETOS DEL JUEGO	 

	GameList<SceneObject> sceneObjects;	

	Cannon* player;

	Mothership* mother;
	
	//GENERADOR ALEATORIO
	std::mt19937_64 randomGenerator;

	//numero aleatorio de disparadores y tipos aleatorios de aliens, para randomMode
	const bool randomMode = false;
	const int shootersPercent = 60;

	//barra de informacion
	InfoBar* infoB;

	//puntuacion
	int score = 0;

	//audio,sacar a una clase

	bool musicOn = false;

	SDL_AudioSpec wavSpec;
	Uint32 wavLength;
	Uint8* wavBuffer;

	SDL_AudioDeviceID deviceId;


	bool exit;

	bool win;


	//carga de objetos de un archivo
	void ReadMap(const std::string mapPath);

	
	
	//inicializa el randomMode, a lo mejor esto hay que cambiarlo
	void RandomMode();
	//carga la musica de fondo del juego
	void LoadMusic();


	//cargar partida
	void LoadGame(std::string savePath);

public:
	//bucle de juego
	void Render() const override;
	void Update() override;
	void HandleEvent(const SDL_Event& ev) override;


	void SaveGame(std::string file);
		
	//disparar laser
	void fireLaser(Vector2D<> pos,char color);

	//hace el calculo de colisiones
	bool collisions(const Laser* laser);
	bool collisions(const Bomb* bomb);
	bool collisions(SDL_Rect rect, char color);

	//devuelve un numero aleatorio con distrubucion uniforme en el rango dado
	int getRandomRange(int min, int max);

	//los aliens la llaman cuando llegan al umbral inferior de la pantalla
	void aliensLimitBotton();

	void UpdateLifesUI();

	void UpdateScoreUI();


	void HasDied(GameList<SceneObject>::anchor an);


	void HasDied(GameList<GameObject,true>::anchor an);

	void AlienDied(int type);

	void UfoDied(Ufo* ufo);

	void playerDied() { exit = true; win = false; }

	bool mayGrantReward(SDL_Rect rewardRect)const;

	void PlayerInvencible();

	//constructor
	PlayState(Game* game,std::string fileName= MAP_PATH);

	//destructor
	~PlayState();
};






#endif // !PlayState_H__H_

