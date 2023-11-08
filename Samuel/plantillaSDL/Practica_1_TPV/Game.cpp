#include <iostream>
#include<fstream>//para flujo de archivos entrada salida
#include<random>
#include "SDL.h"
#include "Game.h"
#include "Alien.h"

#include "checkML.h"


void Game::InitializeSDL() {
	//inicializar sdl
	SDL_Init(SDL_INIT_EVERYTHING);

	//crear la ventana
	window = SDL_CreateWindow("Practica 1 TPV", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWidth, winHeight, SDL_WINDOW_SHOWN);

	//crear el renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//si ha fallado la carga salir, sino codigo del programa
	if (window == nullptr || renderer == nullptr)
		throw std::string("Error loading SDL window or renderer");
}

void Game::LoadTextures(const std::vector<TextureInfo>& textInfo) {
	//crear las texturas
	for (int i = 0; i < NUM_TEXTURAS; i++) {
		arrayTexturas[i] = new Texture(renderer, (TEXTURE_ROOT + textInfo[i].fileName).c_str(),
			textInfo[i].horizontalFrames, textInfo[i].verticalFrames);

		/* ya hay un throw en la carga de superficies, no haria falta
		if (arrayTexturas[i] == nullptr)
			throw std::string("error al cargar la textura con ruta "+ (TEXTURE_ROOT + textInfo[i].fileName));
		*/
	}

}

void Game::RandomMode() {
	int porcentajeOtros = shootersPercent + ((100 - shootersPercent) / 2);

	for (int i = 0; i < aliens.size(); i++) {
		int r = getRandomRange(0, 100);

		if (r < shootersPercent)		aliens[i]->setType(0);
		else if (r <= porcentajeOtros)	aliens[i]->setType(1);
		else							aliens[i]->setType(2);

	}
}

void Game::LoadMusic() {
	//audio copiado de internet

	// load WAV file	

	SDL_LoadWAV("sonidos/theme.wav", &wavSpec, &wavBuffer, &wavLength);

	// open audio device

	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	// play audio

	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}

//constructor
Game::Game(const std::vector<TextureInfo>& textInfo)
{
	InitializeSDL();
	
	LoadTextures(textInfo);


	//inicializar los objetos
	ReadMap("mapas/original.txt");

	infoB = new InfoBar(arrayTexturas[SPACESHIP],arrayTexturas[FONT], this, PLAYER_LIFES);

	//inicializar direcion de los aliens
	aliensDirection = Vector2D<>(1, 0);// se mueven hacia la derecha

	//inicializar el generador aleatorio con una semilla 
	randomGenerator = std::mt19937_64(time(nullptr));

	//modo aliens aleatorios
	if (randomMode) RandomMode();
	
	LoadMusic();
	
};

//destructor
Game::~Game() {
	//delete de las texturas(dentro se hace el SDL_DestroyTexture)
	for (int i = 0; i < NUM_TEXTURAS; i++) {
		delete arrayTexturas[i];
	}

	//delete de los objetos(eran punteros)

	delete player;

	delete infoB;

	for (int i = 0; i < aliens.size(); i++) {
		delete aliens[i];
	}
	for (int i = 0; i < bunkers.size(); i++) {
		delete bunkers[i];
	}
	for (int i = 0; i < lasers.size(); i++) {
 		delete lasers[i];
	}


	// clean up de la musicas
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);

	//destructores(renderer window, y sdl quit)
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Render()const {

	//clear de la pantalla(si se va a repintar toda la pantalla opcional)
	SDL_RenderClear(renderer);

	//render del background
	arrayTexturas[STARS]->render();
	

	//render de los objetos

	player->Render();
	
	for (int i = 0; i < lasers.size(); i++) {//los lasers van por detras
		lasers[i]->Render();
	}
	for (int i = 0; i < aliens.size(); i++) {
		aliens[i]->Render();
	}
	for (int i = 0; i < bunkers.size(); i++) {
		bunkers[i]->Render();
	}

	infoB->Render();

	//renderizar todo la cola
	SDL_RenderPresent(renderer);
}

void Game::Update() {
	//update de los objetos
	//refactorizar, cuando se implemente herencia 


	//update del player
	if (!player->Update()) exit = true;

	//cambiar por whiles 
	int i;

	//update de los aliens
	i = 0;
	while (i < aliens.size()) {
		if (!aliens[i]->Update()) {
			score += aliens[i]->getType() == 0 ? 30 : aliens[i]->getType() == 1 ? 20 : 10;//actualizar la puntuacion
			delete aliens[i];
			aliens.erase(aliens.begin() + i);
		}
		else i++;
	}

	//update de los bunkers
	i = 0;
	while (i < bunkers.size()) {
		if (!bunkers[i]->Update()) {
			delete bunkers[i];
			bunkers.erase(bunkers.begin() + i);
		}
		else i++;
	}

	//update de los lasers
	i = 0;
	while (i < lasers.size()) {
		if (!lasers[i]->Update()) {
			delete lasers[i];
			lasers.erase(lasers.begin() + i);
		}
		else i++;
	}


	//cambio de direccion de los aliens
	if(_goDown){
		aliensDirection = Vector2D<>(nextDirX, 0);//no seria mejor con un set?
		_goDown = false;
	}

	if (cannotM) {
		nextDirX = -1 * aliensDirection.getX();
		cannotM = false;
		aliensDirection = Vector2D<>(0, 1);
	}

	//aumento de velocidad de los aliens, en relacion a la puntuacion
	if (score >= scoreToIncreaseVelocity) {
		Alien::IncreaseVelocity();
		scoreToIncreaseVelocity += 100;
	}

	UpdateScoreUI();
	//condicion de victoria
	if (aliens.size() == 0){
		exit = true;//añadir comentario de victoria
	} 



	currentRenameFrames++;


}

void Game::HandleEvents() {
	SDL_Event evento;

	//carga los eventos 
	while (SDL_PollEvent(&evento) && !exit) {
		//trata los eventos en funcion de su tipo()
		if (evento.type == SDL_QUIT) {
			exit = true;
		}
		else {
			if (evento.type == SDL_KEYDOWN && evento.key.keysym.scancode == SDL_SCANCODE_G) {
				SaveGame();
				saving = true;
				currentRenameFrames = 0;
			}
			else if (evento.type == SDL_KEYDOWN && evento.key.keysym.scancode == SDL_SCANCODE_C) {
				LoadGame();
			}
			if (saving) {

			}
			//handleEvents de los objetos
			player->HandleEvents(evento);		
		}
	}
}

void Game::Run() {

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

void Game::ReadMap(const std::string mapPath) {

	std::ifstream map;

	map.open(mapPath);

	if (map.fail()) {
		throw std::string("Error al cargar el mapa");//lanzar error
	}

	int objectType;

	int v1, v2, v3;//valores auxiliares
	

	while (!map.eof()) {

		map >> objectType;

		if (map.eof()) return;//para detectar el final del archivo

		map >> v1 >> v2;

		if (objectType == 0) { //cannon		
			player = new Cannon(arrayTexturas[SPACESHIP], Point2D<>(v1, v2), this, PLAYER_LIFES);
		}
		else if (objectType == 1) { //alien 		
			map >> v3;
			aliens.push_back(new Alien(arrayTexturas[ALIENS], Point2D<>(v1, v2), v3, this));
		}
		else if (objectType == 2) { // bunker		
			bunkers.push_back(new Bunker(arrayTexturas[BUNKER], Point2D<>(v1, v2), BUNKER_LIFES));
		}	
	}

}




void Game::cannotMove() {
	cannotM = true;
}

void Game::goDown() {
	_goDown = true;
}

void Game::fireLaser(Vector2D<> pos,bool originA) {
	lasers.push_back(new Laser(pos, originA, this));
}


//refactorizar, cuando se implemente herencia 
bool Game::collisions(const Laser* laser) {
	bool colision = false;
	
	SDL_Rect laserRect = laser->getRect();
	SDL_Rect other;
	int i;
	
	//colision con el player,solo cuando el laser es de los aliens

	if (laser->getOriginA()) {
		other = player->getRect();
		if (SDL_HasIntersection(&(laserRect), &(other))) {
			colision = true;
			player->Hit();
		}
	}

	//colisiones con los demas objetos, si usaramos herencia esto se podria agrupar en una unica funcion
	//pasar a 3 funciones separadas

	//colisiones con los aliens, solo cuando el laser es del jugador

	if (!laser->getOriginA()) {
		i = 0;
		while (i < aliens.size() && !colision) {
			other = aliens[i]->getRect();
			if (SDL_HasIntersection(&(laserRect), &(other))) {
				colision = true;
				aliens[i]->Hit();
			}
			i++;
		}
	}

	//colisiones con los bunkers,siempre
	i = 0;
	while (i < bunkers.size() && !colision) {
		other = bunkers[i]->getRect();
		if (SDL_HasIntersection(&(laserRect), &(other))) {
			colision = true;
			bunkers[i]->Hit();
		}
		i++;
	}


	//colisiones con los lasers, no comparar lasers del mismo origen
	i = 0;
	while (i < lasers.size() && !colision) {

		if (laser->getOriginA() != lasers[i]->getOriginA()) {

			other = lasers[i]->getRect();
			if (SDL_HasIntersection(&(laserRect), &(other))) {
				colision = true;
				lasers[i]->Hit();
			}
		}

		i++;
	}	

	return colision;
}



int Game::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}


void Game::aliensLimitBotton() {
	exit = true;//cambiar por un mensaje de los aliens demasiado abajo
}

void Game::UpdateLifesUI() {
	infoB->UpdateCurrentLifes(player->getLifes());
}

void Game::UpdateScoreUI() {
	infoB->UpdateCurrentScore(score);
}


//falta guardar mas datos
void Game::SaveGame() {
	std::ofstream out;

	out.open("partidas_guardadas/tmp.txt");

	//puntuacion
	out << score << std::endl;
	//info player
	out << 0 << " " << player->getRect().x << " " << player->getRect().y << " " << player->getLifes();

	out << std::endl;

	//info aliens
	for (int i = 0; i < aliens.size(); i++) {
		out << 1 << " " << aliens[i]->getRect().x << " " <<
			aliens[i]->getRect().y << " " << aliens[i]->getType() << std::endl;
	}

	//info bunkers
	for (int i = 0; i < bunkers.size(); i++) {
		out << 2 << " " << bunkers[i]->getRect().x << " " <<
			bunkers[i]->getRect().y << " " << bunkers[i]->getLifes() << std::endl;
	}


}

void Game::LoadGame() {
	std::ifstream in;

	in.open("partidas_guardadas/save.txt");

	//puntuacion
	in >> score;

	int objectType;

	int v1, v2, v3;//valores auxiliares

	bool exit = false;
	
	//borrar las entidades que hay actualmente,hay que sacar esto a un metodo
	for (int i = 0; i < aliens.size(); i++) {
		delete aliens[i];
	}
	for (int i = 0; i < bunkers.size(); i++) {
		delete bunkers[i];
	}
	for (int i = 0; i < lasers.size(); i++) {
		delete lasers[i];
	}

	aliens.resize(0);
	bunkers.resize(0);
	lasers.resize(0);


	while (!in.eof() && !exit) {

		in >> objectType;

		if (in.eof()) exit = true;//para detectar el final del archivo

		in >> v1 >> v2 >> v3;


		if (objectType == 0) { //cannon		
			player->setPos(Point2D<>(v1, v2));
			player->setLifes(v3);
		}
		else if (objectType == 1) { //alien 
		
			aliens.push_back(new Alien(arrayTexturas[ALIENS], Point2D<>(v1, v2), v3, this));
		}
		else if (objectType == 2) { // bunker	
			
			bunkers.push_back(new Bunker(arrayTexturas[BUNKER], Point2D<>(v1, v2), BUNKER_LIFES));
			bunkers[bunkers.size() - 1]->setLifes(v3);
		}

	}

	//actualizar UI 
	UpdateLifesUI();
	UpdateScoreUI();

}

void Game::TryRename(SDL_Event ev) {

	SDL_Scancode code = ev.key.keysym.scancode;
	
	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code >= 30 && code <= 38) {
			slotNumber = code - 29;
			saving = false;
			std::rename("","");
		}	
	}
	
}