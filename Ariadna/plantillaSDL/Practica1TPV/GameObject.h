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

	// estos metodos son virtuales porque esta clase no define los renders de los gameobjects que hereden de ella
	// (enlace dinámico) Los render se definirán en cada gameobject según qué hagan
	virtual void Render() const = 0;
	virtual void Update() = 0;
	virtual void Save(std::ostream&) const = 0;

	// constructora
	GameObject(Game* game) : game(game) {};
	// hay que poner una destructora virtual (?)
	virtual ~GameObject() {};
};
