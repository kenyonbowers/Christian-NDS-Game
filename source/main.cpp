#include <stdio.h>
#include <nds.h>
#include <nf_lib.h>
#include "player.h"
#include "collisionBox.h"
#include "weapon.h"

// Player Objects
Player player1(0);
Player player2(1);

// Collision Box Objects
CollisionBox player1CollisionBox(0, 0, 16, 16);
CollisionBox player2CollisionBox(0, 0, 16, 16);
CollisionBox sword1CollisionBox(0, 0, 8, 8);
CollisionBox sword2CollisionBox(0, 0, 8, 8);

// Weapon Objects
Weapon player1Weapon(1);
Weapon player2Weapon(1);

int timer = 0;
char p1health[32];
char p2health[32];
char p1lives[32];
char p2lives[32];

int player1Speed = 1.5;
int player2Speed = 1.5;

int player1DelayFrames = 0;
int player2DelayFrames = 0;

int player1ReloadTime = 0;
int player2ReloadTime = 0;

int player1JumpForce = 1;
int player2JumpForce = 1;

int player1JumpFrames = 0;
int player2JumpFrames = 0;
int player1FramesInAir = 0;
int player2FramesInAir = 0;

int ammoStartIndex = 2;
int ammoEndIndex = 11;
int swordStartIndex = 12;
int swordEndIndex = 13;

bool player1SwordOut = false;
bool player2SwordOut = false;
bool sword1DoneDamage = false;
bool sword2DoneDamage = false;

int player1SwordFrames = 0;
int player2SwordFrames = 0;

void updateHUD()
{
	sprintf(p1lives, "LIVES: %d", player1.getLives());
	sprintf(p2lives, "LIVES: %d", player2.getLives());
	sprintf(p1health, "HEALTH: %d", player1.getHealth());
	sprintf(p2health, "HEALTH: %d", player2.getHealth());

	NF_ClearTextLayer(0, 0);

	NF_WriteText(0, 0, 1, 3, p1health);
	NF_WriteText(0, 0, 1, 2, p1lives);

	NF_WriteText(0, 0, 21, 3, p2health);
	NF_WriteText(0, 0, 22, 2, p2lives);
	NF_UpdateTextLayers();
}

bool CollisionCheck(CollisionBox r1, CollisionBox r2){
	return(r1.getX() < r2.getX() + r2.getWidth() && r1.getX() + r1.getWidth() > r2.getX() && r1.getY() < r2.getY() + r2.getHeight() && r1.getY() + r1.getHeight() > r2.getY());
}

void BattleStage() {
	NF_LoadTiledBg("backgrounds/Stage_1", "Stage_1", 256, 256);
	NF_CreateTiledBg(0, 1, "Stage_1");
	NF_LoadColisionBg("collision_maps/Stage_1", 0, 256, 200);

	player1.setY(143);
	player1.setX(50);

	player1.setLives(3);
	player2.setLives(3);

	player1.setHealth(10);
	player2.setHealth(10);

	while(1) 
	{
		scanKeys();
		
		if (keysHeld() & KEY_START)
		{
			break;
		}

		updateHUD();
		
		//NF_CreateSprite(0, 0, 0, 1, snake.getApple().getX(), snake.getApple().getY());
		/*for (int i = 0; i < snake.getSize(); i++)
		{
			NF_CreateSprite(0, i + 1, 0, 0, snake.getSegment(i).getX(), snake.getSegment(i).getY());
			NF_CreateSprite(0, i + snake.getSize() + 1, 0, 2, snake.getSegment(i).getX(), snake.getSegment(i).getY() + 3);
		}*/
		
		// Player 1
		if (keysHeld() & KEY_LEFT)
		{
			player1.setX(player1.getX() - player1Speed);
		}
		else if (keysHeld() & KEY_RIGHT)
		{
			player1.setX(player1.getX() + player1Speed);
		}

		if(player1.getX() > player2.getX()){
			player1.setDirection(true);
		}
		else if(player1.getX() < player2.getX()){
			player1.setDirection(false);
		}
		NF_HflipSprite(0, 0, player1.getDirection());

		if(player1.getJumpState() == 0){
			bool canJump = true;
			int amount = 0;
			for(int i = 0; i < 16; i++){
				if(NF_GetPoint(0, player1.getX() + i, player1.getY() + 17) == 2){
					amount++;
				}
				if(amount == 16){
					player1.setJumpState(3);
					canJump = false;
				}
			}
			if(canJump){
				if(keysDown() & KEY_UP){
					player1.setJumpState(1);
				}	
			}	
		}
		else if(player1.getJumpState() == 1){
			if(player1JumpFrames != player1.getJumpFrames()){
				player1.setY(player1.getY() - player1JumpForce);
				player1JumpFrames++;
			}
			else{
				player1.setJumpState(2);
				player1JumpFrames = 0;
			}
		}
		else if(player1.getJumpState() == 2){
			if(player1FramesInAir != player1.getTimeInAir()){
				player1FramesInAir++;
			}
			else{
				player1.setJumpState(3);
				player1FramesInAir = 0;
			}
		}
		else if(player1.getJumpState() == 3){
			bool collide = false;
			for(int i = 0; i < 16; i++){
				if(NF_GetPoint(0, player1.getX() + i, player1.getY() + 17) == 0){
					collide = true;
				}
			}
			for(int i = 0; i < 16; i++){
				if(NF_GetPoint(0, player1.getX() + i, player1.getY() + 17) == 1 && NF_GetPoint(0, player1.getX() + i, player1.getY() + 16) != 1 && NF_GetPoint(0, player1.getX() + i, player1.getY() + 15) != 1){
					collide = true;
				}
			}
			if(collide == false){
				player1.setY(player1.getY() + player1.getFallSpeed());
			}
			else{
				player1.setJumpState(0);
			}
		}

		if(player1.getAmmo() == 0){
			player1DelayFrames--;
			if(player1DelayFrames == 0){
				player1.setAmmo(5);
			}
		}

		if(player1SwordOut){
			player1SwordFrames++;
			NF_CreateSprite(0, swordStartIndex, 1, 1, player1.getWeaponX(), player1.getWeaponY());
			if(player1SwordFrames == 15){
				NF_DeleteSprite(0, swordStartIndex);
				player1SwordFrames = 0;
				player1SwordOut = false;
				sword1DoneDamage = false;
			}
			
		}

		if(keysDown() & KEY_DOWN){
			if(player1Weapon.getType() == 0){
				if(player1DelayFrames >= 0){
					player1DelayFrames = 0;
					player1SwordOut = true;
					NF_HflipSprite(0, swordStartIndex, player1.getDirection());
				}
			}
			/*else if(player1Weapon.getType() == 1){
				if(player1.getAmmo() < 0){
					player1.setAmmo(player1.getAmmo() - 1);
					NF_CreateSprite();
					if(player1.getAmmo() == 0){
						player1DelayFrames = player1.getReloadTime();
					}
				}
			}*/
		}

		// Player 2
		if (keysHeld() & KEY_Y)
		{
			player2.setX(player2.getX() - player2Speed);
		}
		else if (keysHeld() & KEY_A)
		{
			player2.setX(player2.getX() + player2Speed);
		}

		if(player2.getX() > player1.getX()){
			player2.setDirection(true);
		}
		else if(player2.getX() < player1.getX()){
			player2.setDirection(false);
		}
		NF_HflipSprite(0, 1, player2.getDirection());

		if(player2.getJumpState() == 0){
			bool canJump = true;
			int amount = 0;
			for(int i = 0; i < 16; i++){
				if(NF_GetPoint(0, player2.getX() + i, player2.getY() + 17) == 2){
					amount++;
				}
				if(amount == 16){
					player2.setJumpState(3);
					canJump = false;
				}
			}
			if(canJump){
				if(keysDown() & KEY_X){
					player2.setJumpState(1);
				}	
			}	
		}
		else if(player2.getJumpState() == 1){
			if(player2JumpFrames != player2.getJumpFrames()){
				player2.setY(player2.getY() - player2JumpForce);
				player2JumpFrames++;
			}
			else{
				player2.setJumpState(2);
				player2JumpFrames = 0;
			}
		}
		else if(player2.getJumpState() == 2){
			if(player2FramesInAir != player2.getTimeInAir()){
				player2FramesInAir++;
			}
			else{
				player2.setJumpState(3);
				player2FramesInAir = 0;
			}
		}
		else if(player2.getJumpState() == 3){
			bool collide = false;
			for(int i = 0; i < 16; i++){
				if(NF_GetPoint(0, player2.getX() + i, player2.getY() + 17) == 0){
					collide = true;
				}
			}
			for(int i = 0; i < 16; i++){
				if(NF_GetPoint(0, player2.getX() + i, player2.getY() + 17) == 1 && NF_GetPoint(0, player2.getX() + i, player2.getY() + 16) != 1 && NF_GetPoint(0, player2.getX() + i, player2.getY() + 15) != 1){
					collide = true;
				}
			}
			if(collide == false){
				player2.setY(player2.getY() + player2.getFallSpeed());
			}
			else{
				player2.setJumpState(0);
			}
		}

		if(player2.getAmmo() == 0){
			player2DelayFrames--;
			if(player2DelayFrames == 0){
				player2.setAmmo(5);
			}
		}

		if(player2SwordOut){
			player2SwordFrames++;
			NF_CreateSprite(0, swordEndIndex, 1, 1, player2.getWeaponX(), player2.getWeaponY());
			if(player2SwordFrames == 15){
				NF_DeleteSprite(0, swordEndIndex);
				player2SwordFrames = 0;
				player2SwordOut = false;
				sword2DoneDamage = false;
			}
		}

		if(keysDown() & KEY_B){
			if(player2Weapon.getType() == 0){
				if(player2DelayFrames >= 0){
					player2DelayFrames = 0;
					player2SwordOut = true;
					NF_HflipSprite(0, swordEndIndex, player2.getDirection());
				}
			}
			/*else if(player2Weapon.getType() == 1){
				if(player2.getAmmo() < 0){
					player2.setAmmo(player2.getAmmo() - 1);
					NF_CreateSprite();
					if(player2.getAmmo() == 0){
						player2DelayFrames = player2.getReloadTime();
					}
				}
			}*/
		}

		// Collision
		player1CollisionBox.setX(player1.getX());
		player1CollisionBox.setY(player1.getY());
		sword1CollisionBox.setX(player1.getWeaponX());
		sword1CollisionBox.setY(player1.getWeaponY());

		player2CollisionBox.setX(player2.getX());
		player2CollisionBox.setY(player2.getY());
		sword2CollisionBox.setX(player2.getWeaponX());
		sword2CollisionBox.setY(player2.getWeaponY());

		if(player1SwordOut && CollisionCheck(sword1CollisionBox, player2CollisionBox) && !sword1DoneDamage){
			sword1DoneDamage = true;
			if(player2.getHealth() <= 0){
				if(player2.getLives() == 0){
					break;
				}
				else if(player2.getLives() > 1){
					player2.setHealth(10);
					player2.setLives(player2.getLives()-1);
				}
				else{
					player2.setLives(0);
				}
			}
			else{
				player2.setHealth(player2.getHealth() - player1Weapon.getAttack());
			}
		}
		if(player2SwordOut && CollisionCheck(sword2CollisionBox, player1CollisionBox) && !sword2DoneDamage){
			sword2DoneDamage = true;
			if(player1.getHealth() <= 0){
				if(player1.getLives() == 0){
					break;
				}
				else if(player1.getLives() > 1){
					player1.setHealth(10);
					player1.setLives(player1.getLives()-1);
				}
				else{
					player1.setLives(0);
				}
			}
			else{
				player1.setHealth(player1.getHealth() - player2Weapon.getAttack());
			}
		}

		// Create Sprites
		NF_CreateSprite(0, player1.getIndex(), 0, 0, player1.getX(), player1.getY());
		NF_CreateSprite(0, player2.getIndex(), 0, 0, player2.getX(), player2.getY());

		// Set OAM		
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);
		swiWaitForVBlank();
		oamUpdate(&oamMain);	
	}
}

int main(int argc, char **argv) 
{	
	NF_Set2D(0,0);
	NF_SetRootFolder("NITROFS");
	
	NF_InitTiledBgBuffers();
	NF_InitTiledBgSys(0);
	
	NF_InitSpriteBuffers();
	NF_InitSpriteSys(0);

	NF_LoadSpriteGfx("sprites/Player", 0, 16, 32); 
	NF_LoadSpritePal("sprites/Player", 0);
	NF_LoadSpriteGfx("sprites/PlayerHat", 1, 8, 8); 
	NF_LoadSpritePal("sprites/PlayerHat", 1);
	
	NF_VramSpriteGfx(0, 0, 0, true);
	NF_VramSpritePal(0, 0, 0);
	NF_VramSpriteGfx(0, 1, 1, true);
	NF_VramSpritePal(0, 1, 1);
	
	NF_InitTextSys(0);
	
	NF_LoadTextFont("fonts/Default_Font", "Default_Font", 256, 256, 0);
	NF_CreateTextLayer(0, 0, 0, "Default_Font");

	BattleStage();	

	return 0;

}