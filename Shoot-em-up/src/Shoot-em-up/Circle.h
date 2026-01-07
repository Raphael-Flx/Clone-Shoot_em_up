#pragma once
#include "Geometry.h"

struct SDL_Renderer;
class Collider;

class Circle :
	public Geometry
{
private:
	int _precision;

public:
	Circle(int w, int h, int precision = 150) : Geometry(w, h), _precision(precision) {}

	float GetRadius() const;

	void Draw(SDL_Renderer* renderer) override;
};