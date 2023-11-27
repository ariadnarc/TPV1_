#ifndef Ufo_H_
#define Ufo_H_

#include "checkML.h"


#include <iostream>
#include <SDL.h>

#include "SceneObject.h"
#include "texture.h"



class Ufo : public SceneObject {

	Texture* texture;

	enum state{hiddenLeft,right,hiddenRight,left,destroyed};
	
	state currentState;


	int velocityX = 7;
	Vector2D<> dir;

	int waitingFrames;
	
	const static int moveWaitingTime = 2;
	const static int destroyedWaitingTime = 50;

	const static int minWaitingTime = 150;
	const static int maxWaitingTime = 300;

public:

	//constructor por parametros, no esta completo
	Ufo(Game* game, Point2D<> pos);

	//constructor por lectura de archivo
	Ufo(Game* game, Texture* texture, std::istream& in);

	void Save(std::ostream& out) const override;

	void Render() const override;

	void Update() override;

	bool Hit(SDL_Rect rect, char color) override;

};

#endif // !Ufo_H_