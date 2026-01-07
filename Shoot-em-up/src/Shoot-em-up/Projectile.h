#pragma once
#include "GameObject.h"
#include "Collider.h"

class Projectile : public GameObject
{
protected:
	int _dmg;

public:
	Projectile(Geometry* body, Collider* collider, int hp = 1, int speed = 1500, int dmg = 1) : 
		GameObject(body, collider, hp, speed), _dmg(dmg){}

	int GetDamage();
};
