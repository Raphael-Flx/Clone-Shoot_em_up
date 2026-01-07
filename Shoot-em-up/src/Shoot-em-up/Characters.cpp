#include "Character.h"
#include "GameManager.h"
#include <iostream>

void Character::SetShootSpeed(float shootSpeed)
{
	_shootSpeed = shootSpeed;
}

void Character::Update(float deltaTime)
{
	_currentTime += deltaTime;

	if (_currentTime - _shootTime >= 1.f / _shootSpeed)
	{
		_canShoot = true;
	}

	GameObject::Update(deltaTime);
}