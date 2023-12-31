#ifndef CANON_H_
#define CANON_H_

#include "checkML.h"


#include <iostream>
#include "SDL.h"

#include "texture.h"
#include "Vector2D.h"
#include "SceneObject.h"
#include "EventHandler.h"


class PlayState;

class Cannon : public SceneObject, public EventHandler {

	Texture* cannonTexture;
	Texture* shieldTexture;

	Vector2D<> direction;

	const int velocity = 2;

	//booleanos para control del input,cambiar por el otro metodo
	bool rightWASD = false;
	bool rightArrow = false;
	bool leftWASD = false;
	bool leftArrow = false;
	bool space = false;

	const int SHOOT_RATE = 25;

	int shootReload = 0;

	//gestion de diferentes frame rates
	int waitingFrames = 0;
	const static int _frameRate = 1;

	bool invencible = true;

	int invencibleCurrentFrames = 0;
	int invencibleFrames = 300;

	void Move();

	void Shoot();

public:

	//constructor por parametros
	Cannon(PlayState* game, Texture* cannonText,Texture* shieldTexture, Point2D<> pos, int lifes);

	//constructor por lectura de archivo
	Cannon(PlayState* game, Texture* cannonText, Texture* shieldTexture, std::istream& in);

	void Render()const override;

	void Update() override;

	void Save(std::ostream& out) const override;

	bool Hit(SDL_Rect rect, char tLaser) override;

	void handleEvent(const SDL_Event& ev)override; 

	int getLifes() const { return lifesLeft; }

	void Invencible();
};



#endif // !CANON_H_

