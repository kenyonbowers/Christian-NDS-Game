#include "collisionBox.h"
#include <vector>
CollisionBox::CollisionBox(int x, int y, int width, int height)
{
	this->XPos = x;
    this->YPos = y;
    this->SizeX = width;
    this->SizeY = height;
}

int CollisionBox::getX()
{
	return XPos;
}

int CollisionBox::getY()
{
	return YPos;
}

int CollisionBox::getWidth()
{
	return SizeX;
}

int CollisionBox::getHeight()
{
	return SizeY;
}

void CollisionBox::setX(int value) {
	XPos = value;
}

void CollisionBox::setY(int value) {
	YPos = value;
}