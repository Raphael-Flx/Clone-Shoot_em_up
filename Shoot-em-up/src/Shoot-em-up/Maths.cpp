#include "Maths.h"
#include "Circle.h"
#include "Rect.h"
#include <iostream>

void Vector2f::Normalize() 
{
	float length = Maths::GetDistance(0, 0, x, y);

	if (length <= 0)
		return;

	x /= length;
	y /= length;
}

float Maths::GetDistance(float x1, float y1, float x2, float y2)
{
	float distanceX = (x1 - x2) * (x1 - x2);
	float distanceY = (y1 - y2) * (y1 - y2);
	float distance = sqrt(distanceX + distanceY);

	return distance;
}

bool Maths::IntersecCircleCircle(const Circle* c1, const Circle* c2)
{
	Vector2f center1 = c1->GetPosition(0.5f, 0.5f);
	Vector2f center2 = c2->GetPosition(0.5f, 0.5f);

	float distance = Maths::GetDistance(center1.x, center1.y, center2.x, center2.y);
	float radiusDist = c1->GetRadius() + c2->GetRadius();

	return distance <= radiusDist;
}

bool Maths::IntersecCircleRect(const Circle* c1, const Rect* c2)
{
	return false;
}

bool Maths::IntersecRectRect(const Rect* r1, const Rect* r2)
{
	Vector2f pos1 = r1->GetPosition(0.5f, 0.5f);
	Vector2f pos2 = r2->GetPosition(0.5f, 0.5f);

	int width1 = r1->GetWidth();
	int width2 = r2->GetWidth();

	int height1 = r1->GetHeight();
	int height2 = r2->GetHeight();

	bool betweenX = pos1.x + width1 / 2 >= pos2.x - width2 / 2 && pos1.x - width1 / 2 <= pos2.x + width2 / 2;
	bool betweenY = pos1.y + height1 / 2 >= pos2.y - height2 / 2 && pos1.y - height1 / 2 <= pos2.y + height2 / 2;

	if (betweenX && betweenY) {
		return true;
	}

	return false;
}

bool Maths::IntersecRectCircle(const Rect* r1, const Circle* c2)
{
	return false;
}