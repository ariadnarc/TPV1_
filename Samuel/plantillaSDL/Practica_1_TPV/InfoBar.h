#ifndef InfoBar_H_
#define InfoBar_H_

#include"checkML.h"


#include<iostream>
#include<SDL.h>
#include<vector>

#include "GameObject.h"

#include"texture.h"
#include "Font.h"

class PlayState;

class InfoBar : public GameObject{

private:
	//textura para las vidas
	Texture* cannonTexture;
	//textura para la fuente de texto
	Texture* scoreTexture;

	mutable Texture* numberTexture;
	
	Font* font;

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

	int currentScore = 0;

	void RenderLifes() const ;
	void RenderScore() const ;

public:
	
	//constructor
	InfoBar(GameState* game,Font* font,Texture* cannontext,Texture*scoreText,int playerLifes)
		: GameObject(game) , font(font),
			cannonTexture(cannontext),scoreTexture(scoreText),numberTexture(nullptr),
			currentLifes(playerLifes) {};

	//destructor
	~InfoBar() {
		delete numberTexture;
	}

	//metodos heredados de Gam
	void Render() const override;

	void Update() override {};

	void Save(std::ostream& out)const override {};


	//cambiar esto por acceso a las variables?
	void UpdateCurrentLifes(int lifes);
	void UpdateCurrentScore(int score);
};


#endif // !InfoBar_H_