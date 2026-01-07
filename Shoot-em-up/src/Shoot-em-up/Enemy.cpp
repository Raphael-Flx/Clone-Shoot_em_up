#include "Enemy.h"
#include "GameManager.h"
#include <iostream>

void Enemy::SetShootSpeed(float shootSpeed)
{
	_shootSpeed = shootSpeed;
}

void Enemy::Update(float deltaTime)
{
	_currentTime += deltaTime;

	if (_currentTime - _shootTime >= 1.f/_shootSpeed)
	{
		_canShoot = true;
	}

	Spawn(deltaTime);

	Vector2f translation;
	translation.x = _moveDirection.x * _speed * deltaTime;
	translation.y = _moveDirection.y * _speed * deltaTime;

	Move(translation.x, translation.y);
}

void Enemy::Die() 
{
	GameManager::Get()->IncreaseScore(_scoreValue);
}