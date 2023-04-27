#ifndef COLLISIONBOX_H
#define COLLISIONBOX_H

class CollisionBox 
{
  private:
	int XPos;
	int YPos;
	int SizeX;
	int SizeY;
	
  public:
	CollisionBox(int x, int y, int width, int height);
	int getX();
    int getY();
    int getWidth();
    int getHeight();
	void setX(int value);
	void setY(int value);
};

#endif