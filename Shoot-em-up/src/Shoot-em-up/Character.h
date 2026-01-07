#pragma once

#include "GameObject.h"
#include "Collider.h"

class Character : public GameObject
{
protected:
	float _shootSpeed;

	float _currentTime = 0.f;
	float _shootTime = 0.f;

public:
	Character(Geometry* body, Collider* collider, int hp, int speed, float pps) : 
		GameObject(body, collider, hp, speed), _shootSpeed(pps) {}

	void SetShootSpeed(float shootSpeed);

	virtual void Update(float deltaTime) override;
	virtual void Shoot() = 0;
};

