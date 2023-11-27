#ifndef InfoBar_H_
#define InfoBar_H_

#include"checkML.h"


#include<iostream>
#include<SDL.h>
#include<vector>

#include "GameObject.h"

#include"texture.h"



class Game;

class InfoBar : public GameObject{

private:
	//textura para las vidas
	Texture* cannonTexture;
	//textura para la fuente de texto
	Texture* fontTexture;
	
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


	void RenderLifes() const ;
	void RenderScore() const ;


public:
	
	//constructor
	InfoBar(Texture* cannontext,Texture*fontText, Game* game,int playerLifes)
		: GameObject(game), cannonTexture(cannontext),fontTexture(fontText), currentLifes(playerLifes) {};

	//metodos heredados de Gam
	void Render() const override;

	void Update() override {};

	void Save(std::ostream& out)const override {};


	//cambiar esto por acceso a las variables?
	void UpdateCurrentLifes(int lifes);
	void UpdateCurrentScore(int score);
};



#endif // !InfoBar_H_

