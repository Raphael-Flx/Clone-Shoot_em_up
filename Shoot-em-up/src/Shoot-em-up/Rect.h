#pragma once

#include "Geometry.h"

class Collider;

class Rect : public Geometry
{
public :
	Rect(int width, int height) : Geometry(width, height){}

	void Draw(SDL_Renderer* renderer) override;
};

