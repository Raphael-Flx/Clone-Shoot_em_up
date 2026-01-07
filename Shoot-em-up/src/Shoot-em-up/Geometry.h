#pragma once
#include <SDL.h>
#include "Maths.h"

struct SDL_Renderer;

class Geometry
{
protected : 
	float _x;
	float _y;
	int _width;
	int _height;

public:
	Geometry(int width, int height) : _x(0), _y(0), _width(width), _height(height){}
	virtual ~Geometry() {}

	virtual void Draw(SDL_Renderer* renderer) = 0;

	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
	Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f) const;

	int GetHeight() const;
	int GetWidth() const;

	virtual void Resize(int width, int height);
};

