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

	void Save(std::ostream& out) const override;


};

#endif // !Ufo_H_

