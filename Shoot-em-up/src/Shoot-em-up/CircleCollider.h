#pragma once
#include "Circle.h"

#include "Collider.h"

class CircleCollider :
	public Collider
{
public:
	CircleCollider(int width, int height) :
		Collider(Collider::Type::CIRCLE, new Circle(width, height)) {}
	bool IsColliding(Collider* collider) override;
};

