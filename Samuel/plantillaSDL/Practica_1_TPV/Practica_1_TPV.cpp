#include "checkML.h"


#include <iostream>

#include "SDL.h"
#include "SDL_image.h"


#include "Game.h"



using namespace std;
	

int main(int argc, char* argv[]) {

	vector<TextureInfo> texturesInfo;

	texturesInfo.push_back(TextureInfo("aliens.png", 3, 2));
	texturesInfo.push_back(TextureInfo("bunker.png", 1, 4));
	texturesInfo.push_back(TextureInfo("spaceship.png", 1, 1));
	texturesInfo.push_back(TextureInfo("stars.png", 1, 1));
	texturesInfo.push_back(TextureInfo("font.png", 3, 30));
	texturesInfo.push_back(TextureInfo("ufo.png", 1, 2));
	
	Game* game = nullptr;


	//preguntar try caths, logica...

	
	try {
		game = new Game(texturesInfo);
	}
	catch (SDLError error) {//cacheo  de errores de SDL
		cout << error.what();
	}

	//si ha habido  un fallo  cortar la ejecucion
	if (game == nullptr) return 1;

	try {
		game->Run();

		delete game;
	}
	catch(InvadersError error) {
		SDL_ShowSimpleMessageBox(0, "Untitled", error.what(), game->getWindow());
	}
	
	return 0;
}
