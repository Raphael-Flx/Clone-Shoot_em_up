#pragma once

#include "Character.h"
#include "Collider.h"

#define Normal 0
#define Guided 1

class Player : 
	public Character
{
private:
	int _shootMode = Normal;

public:
	Player(Geometry* body, Collider* collider, int hp, int speed, float pps) : 
		Character(body, collider, hp, speed, pps) {}

	int GetShootMode();
	void SetShootMode(int shootMode);

	bool CanShoot();

	void Shoot();
};

