#pragma once
#include "Maths.h"

class Geometry;
struct SDL_Renderer;

class Entity
{
protected:
	Geometry* _body = nullptr;

	Vector2f _moveDirection = { 0.f, 0.f };

public:
	Entity(Geometry* body) : _body(body) {}
	virtual ~Entity();

	virtual void SetPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f);
	virtual void SetDirection(float x, float y);

	Vector2f GetPosition(float anchorX = 0.5f, float anchorY = 0.5f);
	int GetHeight();
	int GetWidth();

	virtual void Update(float deltaTime);
	virtual void Draw(SDL_Renderer* renderer);
	virtual void Resize(int width, int height);
	void Move(float x, float y);
};