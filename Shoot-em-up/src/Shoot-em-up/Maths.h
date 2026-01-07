#pragma once
class Circle;
class Rect;

struct Vector2 
{
	int x;
	int y;
};

struct Vector2f
{
	float x;
	float y;

	void Normalize();
};

namespace Maths
{
	float GetDistance(float x1, float y1, float x2, float y2);

	bool IntersecCircleCircle(const Circle* c1, const Circle* c2);
	bool IntersecCircleRect(const Circle* c1, const Rect* c2);

	bool IntersecRectRect(const Rect* r1, const Rect* r2);
	bool IntersecRectCircle(const Rect* r1, const Circle* c2);
}
