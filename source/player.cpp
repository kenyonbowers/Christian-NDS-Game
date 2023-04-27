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

void Player::setX(int value)
{
	x = value;
}

void Player::setY(int value)
{
	y = value;
}

int Player::getIndex()
{
	return index;
}

int Player::getJumpState(){
	return jumpState;
}

void Player::setJumpState(int value){
	jumpState = value;
}

int Player::getAmmo(){
	return ammo;
}

void Player::setAmmo(int value){
	ammo = value;
}

int Player::getReloadTime(){
	return reloadTime;
}

int Player::getMeleeDelay(){
	return meleeDelay;
}

int Player::getWeaponX(){
	if(direction) {
		//Right
		return x - 8;
	}
	else{
		//Left
		return x + 17;
	}
	return 0;
}

int Player::getWeaponY(){
	return y + 4;
}

bool Player::getDirection(){
	return direction;
}

void Player::setDirection(bool dir){
	direction = dir;
}

int Player::getJumpFrames(){
	return jumpFrames;
}

int Player::getTimeInAir(){
	return inAirFrames;
}

int Player::getFallSpeed(){
	return fallSpeed;
}

void Player::setHealth(int value){
	health = value;
}

void Player::setLives(int value){
	lives = value;
}