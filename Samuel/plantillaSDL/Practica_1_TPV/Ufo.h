#ifndef Ufo_H_
#define Ufo_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>

#include "SceneObject.h"
#include "texture.h"



class Ufo : public SceneObject {

	Texture* texture;

	enum state{visible,hiden,destroyed};
	
	state currentState;

	int waitingFrames;
	int _frameRate;

public:

	//constructor por parametros, no esta completo
	Ufo(Game* game, Point2D<> pos);

	//constructor por lectura de archivo
	Ufo(Game* game, Texture* texture, std::istream& in);

	void Save(std::ostream& out) const override;

	bool Hit(SDL_Rect rect, char color) override { return false; };

	void Render() const override {};

	void Update() override {};

};

#endif // !Ufo_H_

