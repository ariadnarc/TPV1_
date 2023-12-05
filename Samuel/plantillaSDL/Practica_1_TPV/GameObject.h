#ifndef GameObject_H_
#define GameObject_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "gameList.h"


class GameState;//declaracion anticipada

class GameObject {//preguntar por privacidad de los metodos, estan bien publicos?

protected:
	//puntero al estado
	GameState* game;

	//iterador
	GameList<GameObject, true>::anchor anchor = nullptr;
	
public:
	//metodos virtuales
	virtual void Render() const = 0;

	virtual void Update() = 0;

	virtual void Save(std::ostream& out) const = 0;

	//constructor
	GameObject(GameState* game) : game(game) {};
	//destructor (siempre virtual)
	virtual ~GameObject() {};


	void setListAnchor(GameList<GameObject, true>::anchor an) { anchor = an; }

	GameList<GameObject, true>::anchor getListAnchor() { return anchor; }

};

#endif // !GameObject_H_