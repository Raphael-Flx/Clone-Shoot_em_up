#include "GameObject.h"
#include "Geometry.h"
#include "SDL.h"
#include "Collider.h"
#include <iostream>

GameObject::~GameObject()
{
	if (_collider != nullptr)
		delete _collider;
}

void GameObject::SetPosition(float x, float y, float anchorX, float anchorY)
{
	_body->SetPosition(x, y, anchorX, anchorY);
	_collider->SetPosition(x, y, anchorX, anchorY);
}

void GameObject::SetDirection(float x, float y)
{
	_moveDirection.x = x;
	_moveDirection.y = y;

	_moveDirection.Normalize();
}

int GameObject::GetMoveSpeed()
{
	return _speed;
}

int GameObject::GetHp()
{
	return _hp;
}

int GameObject::GetDamage()
{
	return _damage;
}

Collider* GameObject::GetCollider()
{
	return _collider;
}

void GameObject::Update(float deltaTime)
{
	Vector2f translation;

	translation.x = _moveDirection.x * _speed * deltaTime;
	translation.y = _moveDirection.y * _speed * deltaTime;

	Move(translation.x, translation.y);
}

void GameObject::Move(float x, float y)
{
	Vector2f position = GetPosition();
	SetPosition(position.x + x, position.y + y);
}

void GameObject::Resize(int width, int height)
{
	_body->Resize(width, height);
}

void GameObject::ResizeHitbox(int width, int height)
{
	_collider->GetBody()->Resize(width, height);
}

void GameObject::Draw(SDL_Renderer* renderer)
{
	_body->Draw(renderer);

	/*SDL_SetRenderDrawColor(renderer, 100, 255, 100, 180);
	_collider->GetBody()->Draw(renderer);*/
}

bool GameObject::IsColliding(Collider* collider)
{
	return _collider->IsColliding(collider);
}

void GameObject::TakeDamage(int value)
{
	_hp = std::max(0, _hp - value);
}