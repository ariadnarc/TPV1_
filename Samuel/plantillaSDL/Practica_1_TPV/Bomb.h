#ifndef Bomb_H_
#define Bomb_H_


#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "SceneObject.h"
#include "texture.h"


class Bomb : public SceneObject {

	Texture* texture;

	int velocity = 4;

	int waitingFrames = 0;
	int _frameRate = 2;

public:

	Bomb(PlayState* game, Point2D<> pos, int lifesLeft,Texture* texture);


	void Update()  override;

	bool Hit(SDL_Rect rect, char tLaser) override;

	void Render() const override;
	//save vacio pq no se guardan
	void Save(std::ostream& out) const override {};

	void Move();

	bool Colisions();
};



#endif // !Bomb_H_

