#pragma once
#include "Geometry.h"

class Geometry;

class Collider
{
public:
	enum class Type
	{
		CIRCLE,
		RECTANGLE,
	};

protected:
	Type _type;
	Geometry* _body;

public:
	Collider(Type type, Geometry* body) :
		_type(type), _body(body) {}

	~Collider()
	{
		delete _body;
	}

	Geometry* GetBody() const;
	Type GetType() const;

	virtual bool IsColliding(Collider* collider) = 0;
	void SetPosition(int x, int y, float anchorX, float anchorY);
};