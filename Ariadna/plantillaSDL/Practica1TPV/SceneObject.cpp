#include "SDL.h"
#include "checkML.h"
#include "SceneObject.h"
#include <iostream>
#include "Vector2D.h"


SceneObject::SceneObject(Game* game, Point2D<> pos, int width, int height, int lifesleft)
	: GameObject(game), pos(pos), width(width), height(height), lifesleft(lifesleft) {};

SceneObject::SceneObject(Game* game, std::istream& in) : GameObject(game) {

	int x, y;
	in >> x >> y;

	pos = Point2D<>(x, y);

}

void SceneObject::Save(std::ostream& out) const {

}

SDL_Rect SceneObject::GetRect() const {

	SDL_Rect rect;

	rect.x = pos.getX();
	rect.y = pos.getY();
	rect.w = width;
	rect.h = height;

	return rect;
}
