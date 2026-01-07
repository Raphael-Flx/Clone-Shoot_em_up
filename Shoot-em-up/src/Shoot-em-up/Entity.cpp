#include "Entity.h"
#include "Geometry.h"
#include "SDL.h"
#include <iostream>

Entity::~Entity()
{
	{
		if (_body != nullptr)
			delete _body;
	}
}

void Entity::SetPosition(float x, float y, float anchorX, float anchorY)
{
	_body->SetPosition(x, y, anchorX, anchorY);
}

void Entity::SetDirection(float x, float y)
{
	_moveDirection.x = x;
	_moveDirection.y = y;

	_moveDirection.Normalize();
}

Vector2f Entity::GetPosition(float anchorX, float anchorY)
{
	return _body->GetPosition(anchorX, anchorY);
}

int Entity::GetHeight()
{
	return _body->GetHeight();
}

int Entity::GetWidth()
{
	return _body->GetWidth();
}

void Entity::Update(float deltaTime)
{
	Vector2f translation;

	translation.x = _moveDirection.x * deltaTime;
	translation.y = _moveDirection.y * deltaTime;

	Move(translation.x, translation.y);
}

void Entity::Move(float x, float y)
{
	Vector2f position = GetPosition();
	SetPosition(position.x + x, position.y + y);
}

void Entity::Draw(SDL_Renderer* renderer)
{
	_body->Draw(renderer);
}

void Entity::Resize(int width, int height)
{
	_body->Resize(width, height);
}
