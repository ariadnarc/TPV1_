#ifndef GameObject_H_
#define GameObject_H_


#include <iostream>
#include <SDL.h>



#include "checkML.h"



class Game;//declaracion anticipada

class GameObject {//preguntar por privacidad de los metodos, estan bien publicos?

protected:
	//atributos
	Game* game;

	
public:
	//metodos virtuales
	virtual void Render() const = 0;

	virtual void Update() = 0;

	virtual void Save(std::ostream& out) const = 0;


	//constructor
	GameObject(Game* game) : game(game) {};//hace falta???
	//destructor (siempre virtual)
	virtual ~GameObject() {};



};




#endif // !GameObject_H_
