#include "checkML.h"


#include <iostream>
#include<fstream>//para flujo de archivos entrada salida
#include<random>
#include "SDL.h"

#include "Game.h"
#include "PlayState.h"
#include "PauseState.h"
#include "EndState.h"

#include "Alien.h"
#include "Reward.h"


void PlayState::RandomMode() {
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

void PlayState::LoadMusic() {
	//audio copiado de internet

	// load WAV file	

	SDL_LoadWAV("sonidos/theme.wav", &wavSpec, &wavBuffer, &wavLength);

	// open audio device

	deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

	// play audio

	int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);
}



//constructor valido para partidas cargadas y mapas iniciales
PlayState::PlayState(Game* game, std::string fileName) 
	:GameState(game) {

	//inicializar el mothership antes que los aliens
	mother = new Mothership(this);// se mueven hacia la derecha

	//inicializar los objetos
	ReadMap(fileName);

	infoB = new InfoBar(this,game->getFont(), game->getTexture(SPACESHIP), game->getTexture(SCORE), PLAYER_LIFES);

	gameObjects.push_back(mother);
	gameObjects.push_back(infoB);

	//inicializar el generador aleatorio con una semilla 
	randomGenerator = std::mt19937_64(time(nullptr));

	//modo aliens aleatorios
	if (randomMode) RandomMode();

	if (musicOn) {
		LoadMusic();
	}
}

//destructor
PlayState::~PlayState() {
	
	//el delete de los objetos se hara automaticamente al llamar al delete de la lista de objetos

	// clean up de la musicas
	if (musicOn) {
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
	}

}

void PlayState::Render()const {

	//clear de la pantalla(si se va a repintar toda la pantalla opcional)
	game->RenderClear();

	//render del background
	game->getTexture(STARS)->render();
	
	//render de los gameObjects
	GameState::Render();
}

void PlayState::Update() {

	//update de los gameObjects
	GameState::Update();

	UpdateScoreUI();	

	if (mother->haveLanded()) exit = true;
	if (mother->getAlienCount() <= 0) exit = true;
	
	if (exit == true) {
		game->getGameStateMachine()->replaceState(new EndState(game, false));
	}
		
}

void PlayState::HandleEvent(const SDL_Event& ev) {

	GameState::HandleEvent(ev);

	if (ev.type == SDL_KEYDOWN &&
		ev.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {

		//cambiar al estado de pausa
		game->getGameStateMachine()->pushState(new PauseState(game, this));
	}
}

void PlayState::ReadMap(const std::string mapPath) {

	std::ifstream map;

	map.open(mapPath);

	if (map.fail()) {
		throw FileNotFoundError(mapPath);
	}

	int objectType;	
	int line = 0;

	SceneObject* aux = nullptr;

	map >> objectType;


	while (!map.eof()) {		

		if (objectType < 0 || objectType>7) {
			throw FileFormatError(mapPath,line);
		}

		//sacar esto a una funcion?
		if (objectType == CANNON) { //cannon			
			player = new Cannon(this, game->getTexture(SPACESHIP), game->getTexture(REWARD_CANNON),map);
			aux = player;
		}
		else if (objectType == ALIEN) { //alien 
			aux = new Alien(this, game->getTexture(ALIENS), mother, map);		
		}
		else if (objectType == SHOOTER_ALIEN) { // alien disparador
			aux = new ShooterAlien(this, game->getTexture(ALIENS), mother, map);
		}
		else if (objectType == MOTHERSHIP) { //mothership
			mother->Initialize(map);					
		}
		else if (objectType == BUNKER_TYPE) { // bunker		
			aux = new Bunker(this, game->getTexture(BUNKER), map);
		}	
		else if (objectType == UFO_TYPE) { //ovni
			aux = new Ufo(this, game->getTexture(UFO), map);
		}
		else if (objectType == LASER) { //laser
			aux = new Laser(this, map);
		}
		else if (objectType == 7) { //infoBar(score)
			map >> score;
		}

		if (objectType != MOTHERSHIP && objectType != 7 && aux != nullptr) {
			sceneObjects.push_back(aux);
			gameObjects.push_back(aux);
		}

		map >> objectType;
		line++;
	}

}


void PlayState::fireLaser(Vector2D<> pos,char color) {
	SceneObject* aux = new Laser(this, pos, color);

	sceneObjects.push_back(aux);
	gameObjects.push_back(aux);
}


bool PlayState::collisions(const Laser* laser) {
	
	SDL_Rect lRect = laser->getRect();
	char c = laser->getColor();

	GameList<SceneObject>::forward_iterator it = sceneObjects.begin();

	//colision con la lista de SceneObjects
	while (it != sceneObjects.end() && !(*it).Hit(lRect, c)) ++it;
	
	return it != sceneObjects.end();

}


int PlayState::getRandomRange(int min, int max) {
	return std::uniform_int_distribution<int>(min, max)(randomGenerator);
}

void PlayState::aliensLimitBotton() {
	exit = true;//cambiar por un mensaje de los aliens demasiado abajo
}

void PlayState::UpdateLifesUI() {
	infoB->UpdateCurrentLifes(player->getLifes());
}

void PlayState::UpdateScoreUI() {
	infoB->UpdateCurrentScore(score);
}



//falta guardar mas datos, direccion de los aliens,info de las balas, current AtkCD de los aliens...,musica...
void PlayState::SaveGame(std::string file = "partidas_guardadas/tmp.txt") {
	std::ofstream out;

	out.open(file);

	//guardado de todos los objetos de escena
	GameList<SceneObject>::forward_iterator it = sceneObjects.begin();

	while (it != sceneObjects.end()) {
		(*it).Save(out);
		++it;
	}

	//guardado del mothership
	mother->Save(out);

	//guardado de la puntuaciones
	out << 7 << " " << score << " ";

}

void PlayState::LoadGame(std::string savePath) {

	//borrar todos los sceneObjects actuales
	
	GameList<SceneObject>::forward_iterator it = sceneObjects.begin();

	GameList<GameObject, true>::anchor aux;

	while (it != sceneObjects.end()) {	

		aux = (*it).GameObject::getListAnchor();
		sceneObjects.erase((*it).getListAnchor());
		gameObjects.erase(aux);


		++it;
	}


	player = nullptr;

	mother->resetAlienCount();
	
	//leer la partida guardada
	ReadMap(savePath);

	//actualizar UI 
	UpdateLifesUI();
	UpdateScoreUI();

}

void PlayState::ChoseSlot(SDL_Event ev) {

	SDL_Scancode code = ev.key.keysym.scancode;
	
	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code >= 30 && code <= 38) {

			int slotNumber = code - 29;
			
					
			std::string newName = "partidas_guardadas/save" + std::to_string(slotNumber)+ ".txt";
			

			if (std::filesystem::exists(newName)) {
				std::remove(newName.c_str());
			}
			//falta lanzar un error
			int success = std::rename(std::string("partidas_guardadas/tmp.txt").c_str(),newName.c_str());
		}	
	}
	
}

void PlayState::TryLoad(SDL_Event ev) {

	SDL_Scancode code = ev.key.keysym.scancode;

	//manejo del input
	if (ev.type == SDL_KEYDOWN) {
		if (code >= 30 && code <= 38) {

			int slotNumber = code - 29;


			std::string loadFile = "partidas_guardadas/save" + std::to_string(slotNumber) + ".txt";

			LoadGame(loadFile);
			
		}
	}


}


void PlayState::AlienDied(int type) {
	score += SCORE_ALIENS[type];
}

void PlayState::UfoDied(Ufo* ufo) {
	score += SCORE_UFO;

	SDL_Rect rect = ufo->getRect();

	Reward* aux = new Reward(this, Vector2D<>(rect.x, rect.y), 0, 0, 0,game->getTexture(REWARD_SIMBOL),
		[this]() {PlayerInvencible(); });

	gameObjects.push_back(aux);
	sceneObjects.push_back(aux);
}

//eliminar de las 2 listas
void PlayState::HasDied(GameList<SceneObject>::anchor an) {
	GameList<GameObject, true>::anchor aux = an->elem->GameObject::getListAnchor();
	sceneObjects.erase(an);
	gameObjects.erase(aux);
}

//eliminar solo de la lista de gameObjects
void PlayState::HasDied(GameList<GameObject,true>::anchor an) {
	gameObjects.erase(an);
}

//para el reward
bool PlayState::mayGrantReward(SDL_Rect rewardRect)const {
	SDL_Rect playerRect = player->getRect();
	return SDL_HasIntersection(&rewardRect, &playerRect);
}

void PlayState::PlayerInvencible() {
	player->Invencible();
}