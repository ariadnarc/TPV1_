#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Texture.h"
#include "Dog.h"
#include "Game.h"


using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	//ruta de las imagenes
	string dogFile = "../images/dog.png";
	string backGroundFile = "../images/background1.png";
	string helicopterFile = "../images/helicopter.png";

	vector<string> texturesPath{ "../images/dog.png","../images/background1.png","../images/helicopter.png" };

	PlayState game(texturesPath);

	game.Run();

	return 0;
}
