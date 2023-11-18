#include <iostream>
#include <fstream>
#include "texture.h"
#include "Game.h"
#include "InfoBar.h"
#include "checkML.h"
#include "SDL_image.h"
#include "SDL.h"
#include <vector>
#include <random>

using namespace std;

using uint = unsigned int;

Game::Game(const std::vector<TextureInfo>& textInfo) {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (window == nullptr || renderer == nullptr) {

		throw std::string ("Error cargando SDL");
	}

	//rellenar array texturas
	for (int i = 0; i < NUM_TEXTURES; i++) 
	{
		arrayText[i] = new Texture(renderer, (TEXTURE_ROOT + textInfo[i].fileName).c_str(), 
			textInfo[i].horizontalFrames, textInfo[i].verticalFrames);

		/* 
		* no hace falta porque ya salta un error en el constructor de la textura
			if (arrayText[i] == nullptr) {
				throw std::string("Error al cargar la textura con ruta " + (TEXTURE_ROOT + textInfo[i].fileName));
			}
		*/
	}
	

	//inicializar objetos
	ReadMap("maps/original.txt");
	infobar = new InfoBar(this, arrayText[SPACESHIP], player->GetLifes());
	
	//inicializar variables del game
	aliensDirection = Vector2D<>(1,0); //derecha

	// semilla para el random 
	randomGenerator = mt19937_64(time(nullptr));
}

Game::~Game() {

	// destruir array texturas

	for (int i = 0; i < NUM_TEXTURES; i++) {
		delete arrayText[i];
	}

	// destruir elementos de juego
	delete player;

	delete infobar;

	for (int i = 0; i < alienList.size(); i++) {
		delete alienList[i];
	}for (int i = 0; i < bunkerList.size(); i++) {
		delete bunkerList[i];
	}for (int i = 0; i < laserList.size(); i++) {
		delete laserList[i];
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	while (!exit) {
		startTime = SDL_GetTicks();

		handleEvents();
		update();
		render();

		frameTime = SDL_GetTicks() - startTime;
		if (frameTime < FRAME_RATE) 
		{
			SDL_Delay(FRAME_RATE - frameTime);
		}
	}
}

void Game::update() {

	int i = 0;

	if (!player->Update()) {
		exit = true;
	}
	i = 0;
	while (i < alienList.size()) {

		if (!alienList[i]->Update()) { // hace su update y si alguno devuelve false
			delete alienList[i];
			alienList.erase(alienList.begin() + i); // significa que ha muerto y hay que borrarlo
		}
		else { i++; }
	}
	i = 0;
	while (i < bunkerList.size()) {

		if (!bunkerList[i]->Update()) {
			delete bunkerList[i];
			bunkerList.erase(bunkerList.begin() + i);
		}
		else { i++; }
	}
	i = 0;

	while (i < laserList.size()) {

		if (!laserList[i]->Update()) {
			delete laserList[i];
			laserList.erase(laserList.begin() + i); // PROBLEMA: borra todos los lasers para siempre
		}
		else{i++;}
	}

	if (goDown) 
	{
		aliensDirection = Vector2D<>(dirX, 0);
		goDown = false;
	}
	
	if (cannotM) { //si se avisa de que no se puede mover el alien

		dirX = aliensDirection.getX() * -1; // se multiplica por -1 para cambiar la direccion en el eje x
		cannotM = false;
		goDown = true;
		aliensDirection = Vector2D<>(0, 1);
	}
}

void Game::render() const
{
	SDL_RenderClear(renderer);

	//render del fondo
	arrayText[STARS]->render();

	//render de los objetos
	player->Render();
	infobar->Render();

	for (int i = 0; i < alienList.size(); i++) {
		alienList[i]->Render();
	}for (int i = 0; i < bunkerList.size(); i++) {
		bunkerList[i]->Render();
	}for (int i = 0; i < laserList.size(); i++) {
		laserList[i]->Render();
	}

	

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{
	SDL_Event evento;

	while (SDL_PollEvent(&evento) && !exit) {

		if (evento.type == SDL_QUIT) {
			exit = true;
		}
		else {
			player->HandleEvents(evento);
		}
	}
}

void Game::CannotMove() 
{
	cannotM = true;
}

void Game::FireLaser(Point2D<> pos, bool origin) 
{
	//crea un nuevo Laser con posición y origen de alien o cañon
	laserList.push_back(new Laser(pos, origin, this));
}

void Game::ReadMap(std::string path) {
	std::ifstream map;

	map.open(path); //abre el archivo con la ruta que se le pase

	int typeof, v1, v2, v3;

	while (!map.eof()) 
	{
		map >> typeof; //lo primero que lee es el tipo de objeto

		if (map.eof()) return;

		

		if (typeof == 0) // cannon
		{
			map >> v1 >> v2; //lee las coordenadas
			player = new Cannon(arrayText[SPACESHIP], Point2D<>(v1, v2), this, MAX_LIFES); //crea un nuevo player
		}
		else if(typeof == 1) // alien
		{
			map >> v1 >> v2 >> v3; // lee las coordenadas + el tipo
			alienList.push_back(new Alien(arrayText[ALIENS], Point2D<>(v1, v2), v3, this)); // crea un nuevo Alien
		}
		else if (typeof == 2) //bunker
		{
			map >> v1 >> v2; // lee las coordenadas
			bunkerList.push_back(new Bunker(arrayText[BUNKER], Point2D<>(v1, v2), MAX_LIFES)); //crea un nuevo bunker
		}
	}
}

bool Game::Collision(Laser laser) {

	bool colision = false;

	SDL_Rect laserRec = laser.GetRect();
	SDL_Rect otherRect;

	int i = 0;
	while (i < alienList.size() && !colision) // recorre todos los aliens del juego
	{
		otherRect = alienList[i]->GetRect();	//variable auxiliar

		// compruebo si cada alien tiene una colision con el laser que estoy evaluando
		if (SDL_HasIntersection(&otherRect, &laserRec) && !laser.originAlien) 
		{
			alienList[i]->Hit(); // llamo al metodo hit del alien colisionado
			colision = true; // devuelvo true
		}
		else { i++; }
	}

	otherRect = player->GetRect();
	if (SDL_HasIntersection(&laserRec, &otherRect) && laser.originAlien) {
		player->Hit();
		colision = true;
	}

	i = 0;

	while (i < bunkerList.size() && !colision) {

		 otherRect = bunkerList[i]->GetRect();

		if (SDL_HasIntersection(&laserRec, &otherRect)) {
			bunkerList[i]->Hit();
			colision = true;
		}
		else { i++; }
	}

	i = 0;

	while (i < laserList.size() && !colision) {

		 otherRect = laserList[i]->GetRect();

		if (SDL_HasIntersection(&laserRec, &otherRect) && (laser.originAlien != laserList[i]->originAlien)) {
			laserList[i]->Hit();
			colision = true;
		}
		else { i++; }
	}

	return colision;
}

int Game::getRandomRange(int min, int max) {
	return uniform_int_distribution<int>(min, max)(randomGenerator);
}

void Game::updateLifes() {
	infobar->Lifes(player->GetLifes());
}


