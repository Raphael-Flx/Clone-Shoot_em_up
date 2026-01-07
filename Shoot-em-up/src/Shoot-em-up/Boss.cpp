#include "Boss.h"
#include "GameManager.h"
#include "Projectile.h"
#include "Image.h"
#include "RectCollider.h"
#include <cstdlib>
#include <iostream>

void Boss::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	if (_currentTime - _lastPatternTime > PATTERN_TIME)
	{
		ChooseRandomPattern();
		ChooseDirection();
	}

	if (_hp < _maxHp / 3)
	{
		SetShootSpeed(2.f);
	}
}

void Boss::ChooseRandomPattern()
{
	int patternNb = rand() % 2;

	switch (patternNb)
	{
	case 0:
		_currentPattern = Pattern::MultipleShoot;
		break;
	case 1:
		_currentPattern = Pattern::GuidedShoot;
		break;
	}

	_lastPatternTime = _currentTime;
}

void Boss::Spawn(float deltaTime)
{
	if (_canShoot)
	{
		switch (_currentPattern)
		{
		case Pattern::MoveForward:
			MoveForward();
			break;
		case Pattern::MultipleShoot:
			MultipleShoot();
			break;
		case Pattern::GuidedShoot:
			GuidedShoot();
			break;
		}
	}
}

void Boss::Shoot()
{

}

void Boss::MoveForward()
{
	SetDirection(-1, 0);
}

void Boss::ChooseDirection()
{
	int direction = rand() % 3;
	if (direction == 0 && GetPosition().y - _speed * PATTERN_TIME > 0)
		SetDirection(0, -1);
	else if (direction == 2 && GetPosition().y + _speed * PATTERN_TIME < HEIGHT)
		SetDirection(0, 1);
	else
		SetDirection(0, 0);
}

void Boss::MultipleShoot()
{
	Vector2f selfPosition = GetPosition();

	SDL_Renderer* renderer = GameManager::Get()->GetRenderer();

	const char* assetPath = "../../src/Shoot-em-up/Images/EnemyProjectile.png";

	Projectile* projectile = new Projectile(new Image(50, 50, renderer, assetPath), new RectCollider(40, 40));
	projectile->SetPosition(selfPosition.x, selfPosition.y + 10);

	Vector2f direction;

	Vector2f projectilePos = projectile->GetPosition();

	direction.x = -1;
	direction.y = 0;

	projectile->SetDirection(direction.x, direction.y);

	GameManager::Get()->AddEnemyProjectile(projectile);

	_canShoot = false;
	_shootTime = _currentTime;
}

void Boss::GuidedShoot()
{
	Vector2f selfPosition = GetPosition();

	SDL_Renderer* renderer = GameManager::Get()->GetRenderer();

	const char* assetPath = "../../src/Shoot-em-up/Images/bolt1.png";

	Projectile* projectile = new Projectile(new Image(50, 50, renderer, assetPath), new RectCollider(40, 40));
	projectile->SetPosition(selfPosition.x, selfPosition.y + GetHeight() / 2 + 10);

	Projectile* projectile1 = new Projectile(new Image(50, 50, renderer, assetPath), new RectCollider(40, 40));
	projectile1->SetPosition(selfPosition.x, selfPosition.y - GetHeight() / 2 - 10);

	Vector2f direction;
	Vector2f playerPos = GameManager::Get()->GetPlayer()->GetPosition();

	Vector2f projectilePos = projectile->GetPosition();

	direction.x = playerPos.x - projectilePos.x;
	direction.y = playerPos.y - projectilePos.y;

	projectile->SetDirection(direction.x, direction.y);

	GameManager::Get()->AddEnemyProjectile(projectile);

	projectilePos = projectile1->GetPosition();

	direction.x = playerPos.x - projectilePos.x;
	direction.y = playerPos.y - projectilePos.y;

	projectile1->SetDirection(direction.x, direction.y);

	GameManager::Get()->AddEnemyProjectile(projectile1);

	_canShoot = false;
	_shootTime = _currentTime;
}