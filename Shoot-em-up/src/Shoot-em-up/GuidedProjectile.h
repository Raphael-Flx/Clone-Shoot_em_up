#pragma once

#include "Projectile.h"

class GuidedProjectile : public Projectile
{

public:
	GuidedProjectile(Geometry* body, Collider* collider, int hp = 1, int speed = 1500, int dmg = 1) : Projectile(body, collider, hp, speed, dmg) {}
};

