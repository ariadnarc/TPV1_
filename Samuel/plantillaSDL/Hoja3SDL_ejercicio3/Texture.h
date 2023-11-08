#ifndef Texture_h_
#define Texture_h_

#include "checkML.h"

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


class Texture {

	SDL_Texture* texture;
	SDL_Renderer* renderer;

	int widht, height;

public:

	//constructores
	Texture(SDL_Renderer* renderer);
	Texture(SDL_Renderer* renderer,const std::string& file);

	//destructor
	~Texture() { SDL_DestroyTexture(texture); };

	//cargar nueva textura
	void Load(const std::string& file);

	//getters
	int getWidht() { return widht; };
	int getHeight() { return height; };

	//metodos de renderizado, posiblemente se tengan que extender
	void Render(const SDL_Rect* origin,const SDL_Rect* destiny);
	void Render(const SDL_Rect* origin,const SDL_Rect* destiny,double rotation,const SDL_Point* center,SDL_RendererFlip flip);

};




#endif // !1


