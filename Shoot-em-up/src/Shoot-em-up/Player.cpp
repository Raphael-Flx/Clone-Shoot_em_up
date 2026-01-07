#include "Player.h"
#include "Maths.h"

int Player::GetShootMode()
{
	return _shootMode;
}

void Player::SetShootMode(int shootMode)
{
	_shootMode = shootMode;
}

bool Player::CanShoot()
{
	return _canShoot;
}

void Player::Shoot()
{
	_shootTime = _currentTime;
	_canShoot = false;
}