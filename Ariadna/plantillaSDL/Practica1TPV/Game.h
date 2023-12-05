#pragma once
#include "Vector2D.h"
#include "texture.h"
#include "Cannon.h"
#include "Alien.h"
#include "Bunker.h"
#include "InfoBar.h"
#include "Laser.h"
#include "SDL.h"
#include "checkML.h"
#include <iostream>
#include <vector>
#include <random>

using uint = unsigned int;

// no se si esto va aquí exactamente
struct TextureInfo {
    std::string fileName;
    int horizontalFrames, verticalFrames;

	TextureInfo(std::string fname, int hframes, int vframes)
		: fileName(fname), horizontalFrames(hframes), verticalFrames(vframes) {};
};

constexpr uint WIN_WIDTH = 800;
constexpr uint WIN_HEIGHT = 600;
constexpr uint NUM_TEXTURES = 4;
constexpr uint FRAME_RATE = 100;

//constantes del juego
constexpr uint MAX_LIFES = 4;

const std::string TEXTURE_ROOT = "images/"  ;

//enum text
enum TextureName {ALIENS, BUNKER, SPACESHIP, STARS};

class Game {
private:
	// punteros a ventana, renderer y elementos del juego
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	std::vector<Bunker*> bunkerList; 
	std::vector<Alien*> alienList; 
	std::vector<Laser*> laserList; 
	Cannon* player;
	InfoBar* infobar;

	Texture* arrayText[NUM_TEXTURES];

	uint startTime;
	uint frameTime;

	std::mt19937_64 randomGenerator;

	Vector2D<> aliensDirection;

	//enumerado tipos de objetos
	enum ObjectTypes { CANNON, ALIEN, SHOOTER_ALIEN, MOTHERSHIP, BUNKER_TYPE, UFO_TYPE, LASER };

	int dirX;
	bool cannotM = false;
	bool goDown = false;

	bool exit = false;

	void render() const;
	void handleEvents();
	void update();
	void ReadMap(std::string map);
	

public: 
	void FireLaser(Point2D<> pos, bool origin);
	Game(const std::vector <TextureInfo>& texturesInfo);
	~Game();
	void run();

	Vector2D<> GetDirection() const { return aliensDirection; };

	SDL_Renderer* GetRenderer() const { return renderer; };
	void CannotMove();
	bool Collision(Laser laser);

	int getRandomRange(int min, int max);

	void updateLifes();
};
