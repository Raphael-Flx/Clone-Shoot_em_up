#include "DiagonalEnemy.h"
#include "GameManager.h"
#include "Projectile.h"
#include "RectCollider.h"

#include "Image.h"
#include "AssetManager.h"

void DiagonalEnemy::Spawn(float deltaTime)
{
	if (_currentTime > 1.5f)
	{
		SetDirection(-1.f, 0.25f);

		if (_canShoot)
		{
			Shoot();
		}
	}
	else
	{
		SetDirection(-1.f, -0.25f);
	}
}

void DiagonalEnemy::Shoot()
{
	Vector2f selfPosition = GetPosition();

	SDL_Renderer* renderer = GameManager::Get()->GetRenderer();

	const char* assetPath = "../../src/Shoot-em-up/Images/EnemyProjectile.png";

	Projectile* projectile = new Projectile(new Image(60, 60, renderer, assetPath), new RectCollider(40, 40));
	projectile->SetPosition(selfPosition.x, selfPosition.y + GetHeight() + 10);

	Vector2f direction;
	Vector2f playerPos = GameManager::Get()->GetPlayer()->GetPosition();

	direction.x = -1;
	direction.y = 0;

	projectile->SetDirection(direction.x, direction.y);

	GameManager::Get()->AddEnemyProjectile(projectile);

	_shootTime = _currentTime;
	_canShoot = false;
}