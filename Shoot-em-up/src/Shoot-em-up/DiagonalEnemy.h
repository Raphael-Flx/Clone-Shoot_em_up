#pragma once
#include "Enemy.h"

class DiagonalEnemy :
	public Enemy
{
public:
	DiagonalEnemy(Geometry* body, Collider* collider):
		Enemy(body, collider, 700, 3, 225, 0.5) {}

	void Spawn(float deltaTime) override;
	void Shoot() override;
};

