#ifndef PLAYER_h
#define PLAYER_h
#include <vector>
class Player
{
  private:
	int x;
	int y;
	int health;
	int lives;
	int index;
	int jumpState = 0;
	/*
		0 = Idle
		1 = Jump Up
		2 = Idle (In Air)
		3 = Falling
	*/
	int jumpFrames = 30;
	int inAirFrames = 3;
	int ammo = 5;
	int reloadTime = 120;
	int meleeDelay = 30;
	bool direction;
	int fallSpeed = 1.5;
	
  public:
	Player(int index);
	void setX(int value);
	void setY(int value);
	int getX();
	int getY();
	int getHealth();
	void setHealth(int value);
	int getLives();
	void setLives(int value);
	bool hasSegment(int x, int y, bool includeHead);
	int getIndex();
	int getJumpState();
	void setJumpState(int value);
	int getAmmo();
	void setAmmo(int value);
	int getReloadTime();
	int getMeleeDelay();
	int getWeaponX();
	int getWeaponY();
	bool getDirection();
	void setDirection(bool dir);
	int getJumpFrames();
	int getTimeInAir();
	int getFallSpeed();
};
#endif