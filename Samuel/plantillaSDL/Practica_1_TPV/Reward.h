#ifndef Reward_H_
#define Reward_H_

#include "checkML.h"

#include <iostream>
#include <SDL.h>

#include "SceneObject.h"
#include "texture.h"
#include "Button.h"

class Reward : public SceneObject {

	Texture* texture;
	Callback callback;

	int velocity = 4;

	int waitingFrames = 0;
	int _frameRate = 2;

public: 
	Reward(PlayState* game, Point2D<> _pos, int lifesLeft,Texture* texture, Callback callback);
	 
	void Update() override;
	
	void Render() const override;

	void Move();

	bool Hit(SDL_Rect rect, char tLaser) override { return false; };

	//save vacio pq no se guardan
	void Save(std::ostream& out) const override{};
};


#endif // !Reward_H_

