#include "Geometry.h"

void Geometry::SetPosition(float x, float y, float anchorX, float anchorY)
{
	_x = x - _width * anchorX;
	_y = y - _height * anchorY;
}

Vector2f Geometry::GetPosition(float anchorX, float anchorY) const
{
	Vector2f pos;
	pos.x = _x + _width * anchorX;
	pos.y = _y + _height * anchorY;
	return pos;
}

int Geometry::GetHeight() const
{
	return _height;
}

int Geometry::GetWidth() const
{
	return _width;
}

void Geometry::Resize(int width, int height)
{
	_width = width;
	_height = height;
}