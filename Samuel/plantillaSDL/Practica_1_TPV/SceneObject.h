#ifndef SceneObject_H_
#define SceneObject_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>
#include <list>

#include "GameObject.h"
#include "Vector2D.h"
#include "InvadersError.h"

class PlayState;

class SceneObject : public GameObject {

protected:

	Point2D<> pos;

	int width;
	int height;

	int lifesLeft = 1;

	PlayState* playState;

	GameList<SceneObject>::anchor sceneAnchor;

public:

	virtual	bool Hit(SDL_Rect rect, char tLaser) = 0;


	//constructor por parametros
	SceneObject(PlayState* game, Point2D<> _pos, int width, int height, int lifesLeft);

	//constructor por lectura de archivo
	SceneObject(PlayState* game,std::istream& in);


	//hace falta volver a poner el destructor?
	virtual ~SceneObject() {};

	void setListAnchor(GameList<SceneObject>::anchor an) { sceneAnchor = an; }

	virtual void Save(std::ostream& out) const;

	SDL_Rect getRect()const;

	GameList<SceneObject>::anchor getListAnchor() { return sceneAnchor; }

protected:

	//para lanzar excepciones en la lectura de archivos
	template<typename T>
	void readValue(T& v, std::istream& in) {
		in >> v;
		if (in.fail()) {
			throw FileFormatError("",0);
		}
	}

};

#endif // !SceneObject_H_