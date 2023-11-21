#ifndef Ufo_H_
#define Ufo_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>

#include "SceneObject.h"



class Ufo : public SceneObject {

	//enumerado state ...

	int state;

	int _currentFrame;
	int _frameRate;

public:

	//constructor por parametros, no esta completo
	Ufo(Game* game, Point2D<> pos);

	//constructor por lectura de archivo
	Ufo(Game* game, std::istream& in);

	void Save(std::ostream& out) const override;

	bool Hit(SDL_Rect rect, char color) override { return false; };

	void Render() const override {};

	void Update() override {};

};

#endif // !Ufo_H_

