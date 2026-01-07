#include "Circle.h"
#include "SDL.h"
#include "Collider.h"

float Circle::GetRadius() const
{
	return _width / 2.f;
}

void Circle::Draw(SDL_Renderer* renderer)
{
	int precision = 100;

	int radius = _width / 2;

	Vector2f center = GetPosition(.5f, .5f);
	int centerX = center.x;
	int centerY = center.y;

	double perimeter = 2 * M_PI;
	double step = perimeter / precision;

	int lastX = radius * cos(0) + centerX;
	int lastY = radius * sin(0) + centerY;

	for (int i = 1; i <= precision; i++)
	{
		int currentX = radius * cos(step * i) + centerX;
		int currentY = radius * sin(step * i) + centerY;

		SDL_RenderDrawLine(renderer, lastX, lastY, currentX, currentY);

		lastX = currentX;
		lastY = currentY;
	}
}
