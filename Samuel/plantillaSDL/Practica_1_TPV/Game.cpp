#include "checkML.h"


#include <iostream>
#include<fstream>//para flujo de archivos entrada salida
#include<random>
#include "SDL.h"
#include "Game.h"
#include "Alien.h"



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
	}
}

void Game::RandomMode() {
	int porcentajeOtros = shootersPercent + ((100 - shootersPercent) / 2);

	/*
	for (int i = 0; i < aliens.size(); i++) {
		int r = getRandomRange(0, 100);

		if (r < shootersPercent)		aliens[i]->setType(0);
		else if (r <= porcentajeOtros)	aliens[i]->setType(1);
		else							aliens[i]->setType(2);

	}
	*/
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

	//inicializar el mothership antes que los aliens
	mother = new Mothership(this, Vector2D<>(1, 0));// se mueven hacia la derecha
	
	//inicializar los objetos
	ReadMap(MAP_PATH);

	infoB = new InfoBar(arrayTexturas[SPACESHIP],arrayTexturas[FONT], this, PLAYER_LIFES);
	
	//inicializar el generador aleatorio con una semilla 
	randomGenerator = std::mt19937_64(time(nullptr));

	//modo aliens aleatorios
	if (randomMode) RandomMode();
	
	LoadMusic();
	
};

//destructor
Game::~Game() {
	
	//delete de los objetos(eran punteros)

	delete infoB;

	delete mother;

	while (objects.size() > 0) {
		delete objects.front();
		objects.pop_front();
	}

	//delete de las texturas(dentro se hace el SDL_DestroyTexture)
	for (int i = 0; i < NUM_TEXTURAS; i++) {
		delete arrayTexturas[i];
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
	for (SceneObject* ob : objects) ob->Render();

	infoB->Render();

	//renderizar todo la cola
	SDL_RenderPresent(renderer);
}

void Game::Update() {

	//update de los objetos
	
	for (SceneObject* sn : objects) sn->Update();
	
	//delete de los died
	for (auto& it : iteratorsDied) {
		delete (* it);
        objects.erase(it);	
	}

	//ponemos a 0 el vector de muertos
	iteratorsDied.resize(0);


	//update del mothership
	mother->Update();

	//aumento de velocidad de los aliens, en relacion a la puntuacion
	/*
	if (score >= scoreToIncreaseVelocity) {
		Alien::IncreaseVelocity();
		scoreToIncreaseVelocity += 100;
	}
	*/

	//UpdateScoreUI();
	
	//condicion de victoria
	/*
	if (aliens.size() == 0){
		exit = true;//añadir comentario de victoria
	} 
	*/

	
	
	//guardado de slots
	if (saving) {
		currentInputFrames++;
		if (currentInputFrames >= maxInputFrames) {
			saving = false;
			currentInputFrames = 0;

			//de momento no hacer nada
			//hay que buscar el primer archivo libre, si lo hay guardar ahí, sino sobreescribir
		}

	}

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
			if (evento.type == SDL_KEYDOWN && evento.key.keysym.scancode == SDL_SCANCODE_G &&
				!loading) {
				SaveGame();
				saving = true;
				currentInputFrames = 0;
			}
			else if (evento.type == SDL_KEYDOWN && evento.key.keysym.scancode == SDL_SCANCODE_C &&
				!saving) {
				loading = true;
				currentInputFrames = 0;
			}


			if (saving) {
				ChoseSlot(evento);
			}
			if (loading) {
				TryLoad(evento);
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
		
		//prueba para ver cuanto tardan los frames
		//std::cout << frameTime << std::endl;
		
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

	//destruir los objetos actuales, player, mother..., menos las balas para la pool

	map >> objectType;

	while (!map.eof()) {		

		//sacar esto a una funcion?
		if (objectType == CANNON) { //cannon			
			player = new Cannon(this,arrayTexturas[SPACESHIP],map);
			objects.push_back(player);
		}
		else if (objectType == ALIEN) { //alien 
			objects.push_back(new Alien(this,arrayTexturas[ALIENS],mother,map));
		}
		else if (objectType == SHOOTER_ALIEN) { // alien disparador
			objects.push_back(new ShooterAlien(this, arrayTexturas[ALIENS], mother,map));
		}
		else if (objectType == MOTHERSHIP) { //mothership
			mother = new Mothership(this, map);
		}
		else if (objectType == BUNKER_TYPE) { // bunker		
			objects.push_back(new Bunker(this,arrayTexturas[BUNKER],map));
		}	
		else if (objectType == UFO_TYPE) { //ovni
			objects.push_back(new Ufo(this, arrayTexturas[UFO], map));
		}
		else if (objectType == LASER) { //laser
			objects.push_back(new Laser(this, map));
		}
		else if (objectType == 7) { //infoBar(score)
			map >> score;
		}

		//setear el iterador cuando toca
		if (objectType != MOTHERSHIP && objectType != 7) {
			objects.back()->setListIterator(--objects.end());
		}


		map >> objectType;
	}

}


void Game::fireLaser(Vector2D<> pos,char color) {
	objects.push_back(new Laser(this, pos, color));	
	//setear el iterador
	objects.back()->setListIterator(--objects.end());
}


bool Game::collisions(const Laser* laser) {
	
	SDL_Rect lRect = laser->getRect();
	char c = laser->getColor();

	std::list<SceneObject*>::iterator it = objects.begin();

	//colision con la lista de SceneObjects
	while (it != objects.end() && !((*it)->Hit(lRect, c))) ++it;
	
	return it != objects.end();
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


//falta guardar mas datos, direccion de los aliens,info de las balas, current AtkCD de los aliens...,musica...
void Game::SaveGame() {
	std::ofstream out;

	out.open("partidas_guardadas/tmp.txt");

	//puntuacion
	out << score << std::endl;
	//info player
	out << 0 << " " << player->getRect().x << " " << player->getRect().y << " " << player->getLifes();

	out << std::endl;

	//info aliens
	/*
	for (int i = 0; i < aliens.size(); i++) {
		out << 1 << " " << aliens[i]->getRect().x << " " <<
			aliens[i]->getRect().y << " " << aliens[i]->getType() << std::endl;
	}

	//info bunkers
	for (int i = 0; i < bunkers.size(); i++) {
		out << 2 << " " << bunkers[i]->getRect().x << " " <<
			bunkers[i]->getRect().y << " " << bunkers[i]->getLifes() << std::endl;
	}
	*/


}

void Game::LoadGame(std::string savePath) {
	std::ifstream in;

	in.open(savePath);

	if (in.fail()) {
		//no hacer nada
		//return; 
		throw std::string("Error al cargar la partida");//lanzar error
	}
	//puntuacion
	in >> score;

	int objectType;

	int v1, v2, v3;//valores auxiliares

	bool exit = false;
	
	//borrar las entidades que hay actualmente,hay que sacar esto a un metodo
	/*
	for (int i = 0; i < aliens.size(); i++) {
		delete aliens[i];
	}
	for (int i = 0; i < bunkers.size(); i++) {
		delete bunkers[i];
	}
	for (int i = 0; i < lasers.size(); i++) {
		delete lasers[i];
	}
	*/

	/*
	aliens.resize(0);
	bunkers.resize(0);
	lasers.resize(0);
	*/


	in >> objectType;
	
	while (!in.eof() && !exit) {

		in >> v1 >> v2 >> v3;


		if (objectType == 0) { //cannon		
			player->setPos(Point2D<>(v1, v2));
			player->setLifes(v3);
		}
		else if (objectType == 1) { //alien 
		
			//aliens.push_back(new Alien(arrayTexturas[ALIENS], Point2D<>(v1, v2), v3, this));
		}
		else if (objectType == 2) { // bunker	
			
			//bunkers.push_back(new Bunker(arrayTexturas[BUNKER], Point2D<>(v1, v2), BUNKER_LIFES));
			//bunkers[bunkers.size() - 1]->setLifes(v3);
		}

		in >> objectType;
	}

	//actualizar UI 
	UpdateLifesUI();
	UpdateScoreUI();

}

void Game::ChoseSlot(SDL_Event ev) {

	SDL_Scancode code = ev.key.keysym.scancode;
	
	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code >= 30 && code <= 38) {

			slotNumber = code - 29;
			
			saving = false;
			currentInputFrames = 0;
			
			std::string newName = "partidas_guardadas/save" + std::to_string(slotNumber)+ ".txt";
			

			if (std::filesystem::exists(newName)) {
				std::remove(newName.c_str());
			}
			//falta lanzar un error
			int success = std::rename(std::string("partidas_guardadas/tmp.txt").c_str(),newName.c_str());
		}	
	}
	
}

void Game::TryLoad(SDL_Event ev) {

	SDL_Scancode code = ev.key.keysym.scancode;

	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code >= 30 && code <= 38) {

			slotNumber = code - 29;

			loading = false;
			currentInputFrames = 0;

			std::string loadFile = "partidas_guardadas/save" + std::to_string(slotNumber) + ".txt";

			LoadGame(loadFile);
			
		}
	}


}


void Game::HasDied(std::list<SceneObject*>::iterator it) {

	iteratorsDied.push_back(it);
}