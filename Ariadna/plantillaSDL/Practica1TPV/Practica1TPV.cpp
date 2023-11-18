#include <iostream>
#include "checkML.h"
#include "SDL.h"
#include "Game.h"

using namespace std;


int main(int argc, char* argv[])
{
    vector<TextureInfo> texturesInfo;

    texturesInfo.push_back(TextureInfo("aliens.png", 3, 2));
    texturesInfo.push_back(TextureInfo("bunker.png", 1, 4));
    texturesInfo.push_back(TextureInfo("spaceship.png", 1, 1));
    texturesInfo.push_back(TextureInfo("stars.png", 1, 1));

    Game* game = new Game(texturesInfo);

    game->run();

    delete game;

    return 0;
}

