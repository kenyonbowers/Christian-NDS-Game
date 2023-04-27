#include "weapon.h"
#include <stdlib.h>
#include <time.h>
Weapon::Weapon(int attackAmount)
{
	this->attack = attackAmount;
}

int Weapon::getType() 
{
	return type;
} 

int Weapon::getAttack(){
	return attack;
}

void Weapon::setAttack(int value){
	attack = value;
}