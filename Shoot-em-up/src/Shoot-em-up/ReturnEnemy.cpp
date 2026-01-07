#include "ReturnEnemy.h"
#include "GameManager.h"
#include "Projectile.h"
#include "RectCollider.h"

#include "Image.h"
#include "AssetManager.h"

void ReturnEnemy::Spawn(float deltaTime)
{
	if (_currentTime >= 1.f && _currentTime < 2.f)
	{
		SetDirection(0, 0);

		if (_canShoot)
		{
			Shoot();
		}
	}
	else if (_currentTime >= 2.f)
	{
		SetDirection(1, 0);
	}
	else
	{
		SetDirection(-1, 0);
	}
}

void ReturnEnemy::Shoot()
{
	Vector2f selfPosition = GetPosition();

	SDL_Renderer* renderer = GameManager::Get()->GetRenderer();

	const char* assetPath = "../../src/Shoot-em-up/Images/bolt1.png";

	Projectile* projectile = new Projectile(new Image(50, 50, renderer, assetPath), new RectCollider(40, 40));
	projectile->SetPosition(selfPosition.x, selfPosition.y + GetHeight() + 10);

	Projectile* projectile1 = new Projectile(new Image(50, 50, renderer, assetPath), new RectCollider(40, 40));
	projectile1->SetPosition(selfPosition.x, selfPosition.y - GetHeight() - 10);

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

	_shootTime = _currentTime;
	_canShoot = false;
}