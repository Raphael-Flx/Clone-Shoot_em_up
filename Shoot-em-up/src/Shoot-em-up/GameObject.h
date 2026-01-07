#pragma once
#include "Maths.h"
#include "Entity.h"

#define Up 0
#define Down 1
#define Left 2
#define Right 3


class Geometry;
struct SDL_Renderer;

class Collider;

class GameObject : public Entity
{
protected:
	Collider* _collider = nullptr;

	int _hp;
	int _maxHp;
	int _speed;
	int _damage;

	bool _canShoot = true;

public:
	GameObject(Geometry* body, Collider* collider, int hp, int speed, int damage = 1) : Entity(body), _collider(collider), _maxHp(hp), _hp(hp), _speed(speed), _damage(damage) {}
	virtual ~GameObject();

	void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) override;
	void SetDirection(float x, float y) override;

	int GetMoveSpeed();
	int GetHp();
	int GetDamage();
	Collider* GetCollider();
	
	virtual void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void Move(float x, float y);
	void Resize(int width, int height) override;
	void ResizeHitbox(int width, int height);
	bool IsColliding(Collider* collider);
	void TakeDamage(int value);
};