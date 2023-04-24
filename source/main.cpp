#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>
#include "player.h"

const int up = 0;
const int down = 1;
const int left = 2;
const int right = 3;

Player player1(0);
Player player2(1);	
int timer = 0;
int direction = right;
char p1health[32];
char p2health[32];
char p1lives[32];
char p2lives[32];

void updateScore()
{
	sprintf(p1lives, "LIVES: %d", player1.getLives());
	sprintf(p2lives, "LIVES: %d", player2.getLives());
	sprintf(p1health, "HEALTH: %d", player1.getHealth());
	sprintf(p2health, "HEALTH: %d", player2.getHealth());

	NF_ClearTextLayer(0, 0);

	NF_WriteText(0, 0, 1, 3, p1health);
	NF_WriteText(0, 0, 1, 2, p1lives);

	NF_WriteText(0, 0, 20, 3, p2health);
	NF_WriteText(0, 0, 22, 2, p2lives);
	NF_UpdateTextLayers();
}

void reset()
{
	player1 = Player(0);
	direction = right;
	updateScore();
}

int main(int argc, char **argv) 
{
	consoleDemoInit();	
	consoleClear();		
	NF_Set2D(0,0);
	NF_SetRootFolder("NITROFS");
	
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	
	NF_LoadTiledBg("backgrounds/Sprite-0001", "Sprite-0001", 256, 256);
	NF_CreateTiledBg(0, 3, "Sprite-0001");
	
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);
	
	NF_LoadSpriteGfx("sprites/Player", 0, 16, 32); 
	NF_LoadSpritePal("sprites/Player", 0);
	NF_LoadSpritePal("palettes/apple", 1);
	NF_LoadSpritePal("palettes/segment_dropshadow", 2);
	NF_LoadSpritePal("palettes/apple_dropshadow", 3);
	
	NF_VramSpriteGfx(0, 0, 0, true);
	NF_VramSpritePal(0, 0, 0);
	NF_VramSpritePal(0, 1, 1);
	NF_VramSpritePal(0, 2, 2);
	NF_VramSpritePal(0, 3, 3);
	
	NF_InitTextSys(0);
	
	NF_LoadTextFont("fonts/Default_Font", "Default_Font", 256, 256, 0);
	NF_CreateTextLayer(0, 0, 0, "Default_Font");
	
	while(1) 
	{
		scanKeys();
		
		if (keysHeld() & KEY_START)
		{
			break;
		}

		updateScore();
		
		//NF_CreateSprite(0, 0, 0, 1, snake.getApple().getX(), snake.getApple().getY());
		/*for (int i = 0; i < snake.getSize(); i++)
		{
			NF_CreateSprite(0, i + 1, 0, 0, snake.getSegment(i).getX(), snake.getSegment(i).getY());
			NF_CreateSprite(0, i + snake.getSize() + 1, 0, 2, snake.getSegment(i).getX(), snake.getSegment(i).getY() + 3);
		}*/
		NF_CreateSprite(0, player1.getIndex(), 0, 0, player1.getX(), player1.getY());
		

		if (keysHeld() & KEY_UP)
		{
			if (direction != down)
			{
				direction = up;
			}
		}
		else if (keysHeld() & KEY_DOWN)
		{
			if (direction != up)
			{
				direction = down;
			}
		}
		else if (keysHeld() & KEY_LEFT)
		{
			if (direction != right)
			{
				direction = left;
			}
		}
		else if (keysHeld() & KEY_RIGHT)
		{
			if (direction != left)
			{
				direction = right;
			}
		}
		
		/*if (timer >= snake.getDelay())
		{
			if (!snake.move(direction))
			{
				reset();
			}
			updateScore();
			timer = 0;
		} 
		else 
		{
			timer += 1;
		}*/
		
		NF_SpriteOamSet(0);
		swiWaitForVBlank();
		oamUpdate(&oamMain);	
	}

	return 0;

}
