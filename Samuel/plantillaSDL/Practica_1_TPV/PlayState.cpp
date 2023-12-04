#include "checkML.h"


#include <iostream>
#include<fstream>//para flujo de archivos entrada salida
#include<random>
#include "SDL.h"
#include "PlayState.h"
#include "Alien.h"





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

//constructor
PlayState::PlayState()
{
	//inicializar el mothership antes que los aliens
	mother = new Mothership(this);// se mueven hacia la derecha
	
	//inicializar los objetos
	ReadMap(MAP_PATH);

	infoB = new InfoBar(arrayTexturas[SPACESHIP],arrayTexturas[FONT], this, PLAYER_LIFES);
	
	//inicializar el generador aleatorio con una semilla 
	randomGenerator = std::mt19937_64(time(nullptr));

	//modo aliens aleatorios
	if (randomMode) RandomMode();
	
	if (musicOn) {
		LoadMusic();
	}
	
};

//destructor
PlayState::~PlayState() {
	
	//delete de los objetos(eran punteros)

	delete infoB;

	delete mother;

	while (objects.size() > 0) {
		delete objects.front();
		objects.pop_front();
	}

	// clean up de la musicas
	if (musicOn) {
		SDL_CloseAudioDevice(deviceId);
		SDL_FreeWAV(wavBuffer);
	}

}

void PlayState::Render()const {

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

void PlayState::Update() {

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

	UpdateScoreUI();
	

	if (mother->haveLanded()) exit = true;
	if (mother->getAlienCount() <= 0) exit = true;
	
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
	//falta guardado
}

void PlayState::HandleEvents() {
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


			//sacar a una funcion aparte
			/*
			if (saving || loading) {
				SDL_Scancode code = evento.key.keysym.scancode;

				//manejo del input
				if (evento.type == SDL_KEYDOWN) {
					if (code >= 30 && code <= 38) {

						slotNumber = code - 29;

					}
				}
			}
			*/

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

void PlayState::Run() {

	
}

void PlayState::ReadMap(const std::string mapPath) {

	std::ifstream map;

	map.open(mapPath);

	if (map.fail()) {
		throw FileNotFoundError(mapPath);
	}

	int objectType;	
	int line = 0;


	map >> objectType;


	while (!map.eof()) {		

		if (objectType < 0 || objectType>7) {
			throw FileFormatError(mapPath,line);
		}

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
			mother->Initialize(map);					
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
		line++;
	}

}


void PlayState::fireLaser(Vector2D<> pos,char color) {
	objects.push_back(new Laser(this, pos, color));	
	//setear el iterador
	objects.back()->setListIterator(--objects.end());
}


bool PlayState::collisions(const Laser* laser) {
	
	SDL_Rect lRect = laser->getRect();
	char c = laser->getColor();

	std::list<SceneObject*>::iterator it = objects.begin();

	//colision con la lista de SceneObjects
	while (it != objects.end() && !((*it)->Hit(lRect, c))) ++it;
	
	return it != objects.end();
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
void PlayState::SaveGame() {
	std::ofstream out;

	out.open("partidas_guardadas/tmp.txt");

	//guardado de todos los objetos de escena
	for (SceneObject* ob : objects) ob->Save(out);

	//guardado del mothership
	mother->Save(out);

	//guardado de la puntuaciones
	out << 7 << " " << score << " ";

}

void PlayState::LoadGame(std::string savePath) {

	//borrar las entidades que hay actualmente
	while (objects.size() > 0) {
		delete objects.front();
		objects.pop_front();
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

void PlayState::TryLoad(SDL_Event ev) {

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


void PlayState::AlienDied(int type) {
	score += SCORE_ALIENS[type];
}

void PlayState::UfoDied() {
	score += SCORE_UFO;
}

void PlayState::HasDied(std::list<SceneObject*>::iterator it) {
	iteratorsDied.push_back(it);
}