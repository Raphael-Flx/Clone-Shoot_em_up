#pragma once

#include "Character.h"
#include "Collider.h"

class Enemy : 
	public Character
{
protected:
	int _scoreValue;

public:
	Enemy(Geometry* body, Collider* collider, int sv, int hp = 2, int speed = 100, float pps = 1) : Character(body, collider, hp, speed, pps), _scoreValue(sv) {}

	void SetShootSpeed(float shootSpeed);

	virtual void Spawn(float deltaTime) = 0;
	virtual void Update(float deltaTime) override;
	virtual void Shoot() = 0;
	virtual void Die();
};