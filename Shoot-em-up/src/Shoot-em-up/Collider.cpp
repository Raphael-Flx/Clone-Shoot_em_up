#include "Collider.h"

Geometry* Collider::GetBody() const
{
	return _body;
}

Collider::Type Collider::GetType() const
{
	return _type;
}

void Collider::SetPosition(int x, int y, float anchorX, float anchorY)
{
	_body->SetPosition(x, y, anchorX, anchorY);
}