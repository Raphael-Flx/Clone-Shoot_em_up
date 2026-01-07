#include "CircleCollider.h"

#include "Maths.h"
#include "Rect.h"

bool CircleCollider::IsColliding(Collider* collider)
{
	switch (collider->GetType())
	{
	case Collider::Type::CIRCLE:
		return Maths::IntersecCircleCircle((const Circle*)_body, (const Circle*)collider->GetBody());
		break;
	case Collider::Type::RECTANGLE:
		return Maths::IntersecCircleRect((const Circle*)_body, (const Rect*)collider->GetBody());
		break;
	}

	return false;
}