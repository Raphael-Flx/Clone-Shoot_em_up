#include "ForwardEnemy.h"
#include "GameManager.h"
#include "Projectile.h"
#include "RectCollider.h"

#include "Image.h"
#include "AssetManager.h"

void ForwardEnemy::Spawn(float deltaTime)
{
	SetDirection(-1, 0);

	/*if (_canShoot && _currentTime > 0.5f)
	{
		Shoot();
	}*/
}

void ForwardEnemy::Shoot()
{
	Vector2f selfPosition = GetPosition();

	SDL_Renderer* renderer = GameManager::Get()->GetRenderer();

	const char* assetPath = "../../src/Shoot-em-up/Images/EnemyProjectile.png";

	Projectile* projectile = new Projectile(new Image(60, 60, renderer, assetPath), new RectCollider(40, 40));
	projectile->SetPosition(selfPosition.x, selfPosition.y + GetHeight() / 2 + 10);

	Vector2f direction;
	Vector2f playerPos = GameManager::Get()->GetPlayer()->GetPosition();

	direction.x = 0;
	direction.y = 1;

	projectile->SetDirection(direction.x, direction.y);

	GameManager::Get()->AddEnemyProjectile(projectile);

	_shootTime = _currentTime;
	_canShoot = false;
}