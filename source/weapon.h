#ifndef WEAPON_H
#define WEAPON_H

class Weapon 
{
  private:
	int type;
	int attack;
	
  public:
	Weapon(int attackAmount);
	int getType();
	void setType(int value);
	int getAttack();
	void setAttack(int value);
};

#endif