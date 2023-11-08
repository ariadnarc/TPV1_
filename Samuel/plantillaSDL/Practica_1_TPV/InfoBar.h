#ifndef InfoBar_H_
#define InfoBar_H_

#include<iostream>
#include<SDL.h>
#include<vector>

#include"texture.h"


#include"checkML.h"

class Game;

class InfoBar {

private:
	//textura para las vidas
	Texture* cannonTexture;
	//textura para la fuente de texto
	Texture* fontTexture;
	//puntero al game
	Game* game;

	//VARIABLES PARA MOSTRAR LAS VIDAS
	const int lifesStartX = 20;
	const int lifesStartY = 15;

	const int lifesSeparationX = 45;
	const int lifesSeparationY = 25;

	const int lifesPerRow = 5;

	int currentLifes;



	//VARIABLES PARA MOSTRAR LA PUNTUACION
	const int scoreStartX = 480;
	const int scoreStartY = 15;
	const int scoreEndX = 720;


	int currentScore = 0;


	void RenderLifes();
	void RenderScore();


public:
	
	//constructor
	InfoBar(Texture* cannontext,Texture*fontText, Game* game,int playerLifes)
		: cannonTexture(cannontext),fontTexture(fontText), game(game), currentLifes(playerLifes) {};

	void Render();

	void UpdateCurrentLifes(int lifes);
	void UpdateCurrentScore(int score);
};



#endif // !InfoBar_H_

