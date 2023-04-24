#ifndef PLAYER_h
#define PLAYER_h

#include "weapon.h"
#include <vector>
class Player
{
  private:
	Weapon weapon;
	int x;
	int y;
	int health;
	int lives;
	int index;
	
  public:
	Player(int index);
	int getX();
	int getY();
	int getHealth();
	int getLives();
	bool hasSegment(int x, int y, bool includeHead);
	Weapon getWeapon();
	bool move(int direction);
	int getIndex();
};
#endif