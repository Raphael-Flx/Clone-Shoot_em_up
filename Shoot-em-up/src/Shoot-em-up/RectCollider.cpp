#include "RectCollider.h"
#include "Circle.h"
#include "Maths.h"

bool RectCollider::IsColliding(Collider* collider)
{
	switch (collider->GetType())
	{
	case Collider::Type::CIRCLE:
		return Maths::IntersecRectCircle((const Rect*)_body, (const Circle*) collider->GetBody());
		break;
	case Collider::Type::RECTANGLE:
		return Maths::IntersecRectRect((Rect*)_body, (Rect*)collider->GetBody());
		break;
	}

	return false;
}