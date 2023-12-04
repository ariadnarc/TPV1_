#ifndef GameObject_H_
#define GameObject_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>


class PlayState;//declaracion anticipada

class GameObject {//preguntar por privacidad de los metodos, estan bien publicos?

protected:
	//atributos
	PlayState* game;
	
public:
	//metodos virtuales
	virtual void Render() const = 0;

	virtual void Update() = 0;

	virtual void Save(std::ostream& out) const = 0;

	//constructor
	GameObject(PlayState* game) : game(game) {};
	//destructor (siempre virtual)
	virtual ~GameObject() {};

};

#endif // !GameObject_H_