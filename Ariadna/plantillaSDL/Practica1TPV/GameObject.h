#pragma once

#include"SDL.h"
#include"texture.h"
#include"checkML.h"
#include"Cannon.h"
#include"Laser.h"
#include"Alien.h"
#include"Bunker.h"
#include<iostream>

class Game;

class GameObject {
private:

	Game* game;

public:

	virtual void Render() const = 0;
	virtual void Update() = 0;
	//virtual void Save(ostream&) const = 0;

	// hay que poner una destructora virtual (?)
};
