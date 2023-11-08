#include "Texture.h"

#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


using namespace std;

//constructor solo conrenderer
Texture::Texture(SDL_Renderer* _renderer) : renderer(_renderer), texture(nullptr),widht(0),height(0) {};

//constructor con renderer y el path de la imagen
Texture::Texture(SDL_Renderer* _renderer, const string& file) : renderer(_renderer), texture(nullptr) {
	Load(file);
}

void Texture::Load(const string& file) {

	//liberar memoria
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	//cargar la superficie
	SDL_Surface* surface = IMG_Load(file.c_str());
	//cargar la textura
	texture = SDL_CreateTextureFromSurface(renderer,surface);
	//liberar la superficie
	SDL_FreeSurface(surface);
	//asignar el ancho y el alto
	SDL_QueryTexture(texture, nullptr, nullptr, &widht, &height);
}

void Texture::Render(const SDL_Rect* origin, const SDL_Rect* destiny) {
	SDL_RenderCopy(renderer, texture, origin, destiny);
}

void Texture::Render(const SDL_Rect* origin, const SDL_Rect* destiny,
	double rotation, const SDL_Point* center, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(renderer, texture, origin, destiny,rotation,center,flip);
}
