#pragma once

#include"SDL.h"
#include"texture.h"
#include"checkML.h"
#include"Cannon.h"
#include<iostream>

class Game;

class InfoBar {

private:

	Game* game;
	Texture* spaceshipText;
	int lifesLeft;
	const int RectX = 20;
	const int RectY = 20;
	const int separacion = 50;

public:

	InfoBar(Game* _game, Texture* text, int _lifesLeft) :
		game(_game), spaceshipText(text), lifesLeft(_lifesLeft) {};
	void Render() const;
	void Lifes(int lifes);
};