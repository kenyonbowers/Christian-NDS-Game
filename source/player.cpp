#include "player.h"
#include <vector>
Player::Player(int i)
{
	this->index = i;
}

int Player::getX()
{
	return x;
}

int Player::getY()
{
	return y;
}

int Player::getHealth()
{
	return health;
}

int Player::getLives()
{
	return lives;
}

Weapon Player::getWeapon()
{
	return weapon;
}

bool Player::move(int direction)
{
	return true;
}

int Player::getIndex()
{
	return index;
}