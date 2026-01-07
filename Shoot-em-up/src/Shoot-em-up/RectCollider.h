#pragma once
#include "Collider.h"
#include "Rect.h"

class RectCollider :
	public Collider
{
private:

public:
	RectCollider(int width, int height) : 
		Collider(Collider::Type::RECTANGLE, new Rect(width, height)) {}

	bool IsColliding(Collider* collider) override;
};