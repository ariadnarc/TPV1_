#include <iostream>

#include "SDL.h"
#include "SDL_image.h"


#include "Game.h"

#include "checkML.h"

using namespace std;


int main(int argc, char* argv[]) {

	vector<TextureInfo> texturesInfo;

	texturesInfo.push_back(TextureInfo("aliens.png", 3, 2));
	texturesInfo.push_back(TextureInfo("bunker.png", 1, 4));
	texturesInfo.push_back(TextureInfo("spaceship.png", 1, 1));
	texturesInfo.push_back(TextureInfo("stars.png", 1, 1));

	try {
		Game* game;

		game = new Game(texturesInfo);

		game->Run();

		delete game;
	}
	catch (string s) {
		cout << s;
	}

	return 0;
}
