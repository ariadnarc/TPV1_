#ifndef InfoBar_H_
#define InfoBar_H_

#include<iostream>
#include<SDL.h>

#include"texture.h"


#include"checkML.h"

class Game;

class InfoBar {

	Texture* cannonTexture;

	Game* game;

	//VARIABLES PARA MOSTRAR LAS VIDAS
	const int startX = 20;
	const int startY = 15;

	const int lifesSeparationX = 45;
	const int lifesSeparationY = 25;

	const int lifesPerRow = 5;

	int currentLifes;

public:
	
	//constructor
	InfoBar(Texture* cannontext, Game* game,int playerLifes)
		: cannonTexture(cannontext), game(game),currentLifes(playerLifes) {};

	void Render();

	void UpdateCurrentLifes(int lifes);
};



#endif // !InfoBar_H_

