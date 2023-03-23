#include <nds.h>
#include <stdio.h>

#include "graphics.h"
#include "objects.h"
#include "input.h"

#include <ChurchInside.h>

// #include <maxmod9.h>
// #include "soundbank.h"
// #include "soundbank_bin.h"

// Include Art
SpriteEntry OAMCopy[128];
#include <Player.h>
#include <PlayerHat.h>

Sprite Player;
Sprite PlayerHat;
BoundingBox PlayerBounds;

// Global Vars
int PlayerSpeed = 2;
int GravityForce = 2;
int JumpForce = 1;
enum JumpStates {
    falling = 0,
    jumping = 1,
    grounded = 2,
    stationary = 3
};
enum JumpStates JumpState;
int JumpFrames = 20;
int JumpFramesCounter = 0;
int StationaryFrames = 20;
int StationaryFramesCounter = 0;

int playerHealth = 10;
int enemyHealth = 1;

void updateHat(Sprite *hat, Sprite player)
{
    hat->x_pos = player.x_pos;
    hat->y_pos = player.y_pos - 7;
    animateSprite(hat, 1);
    setSprite(hat, &oamMain);
}

int main()
{
    Input pad;

    Player.size.height = 32;
    Player.size.width = 16;
    Player.size.text = SpriteSize_16x32;
    Player.y_pos = 7;

    PlayerHat.size.height = 8;
    PlayerHat.size.width = 8;
    PlayerHat.size.text = SpriteSize_8x8;
    PlayerHat.id = 1;
    PlayerHat.palette = 1;
    PlayerHat.x_pos = 1;

    // Set OAM video modes.
    videoSetMode(MODE_5_2D);
    videoSetModeSub(MODE_0_2D);

    // Setting the banks. Does not include the F bank
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    // Set up oam
    oamInit(&oamMain, SpriteMapping_1D_128, true);
    oamInit(&oamSub, SpriteMapping_1D_128, false);

    // Set bank F
    vramSetBankF(VRAM_F_LCD);
    initSprite(&Player, (u8 *)PlayerTiles, &oamMain);
    dmaCopy(PlayerPal, &VRAM_F_EXT_SPR_PALETTE[0][0], PlayerPalLen);

    initSprite(&PlayerHat, (u8 *)PlayerHatTiles, &oamMain);
    dmaCopy(PlayerHatPal, &VRAM_F_EXT_SPR_PALETTE[1][0], PlayerHatPalLen);
    vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);

    loadBg(ChurchInsideBitmap, ChurchInsidePal, 3);

    while (1)
    {
        swiWaitForVBlank();

        pad = getInput();

        if(pad.held & KEY_LEFT){
			if(Player.x_pos > 0)
                Player.x_pos -= PlayerSpeed;
		}
        else if (pad.held & KEY_RIGHT){
            if (Player.x_pos < 256 - 16)
                Player.x_pos += PlayerSpeed;
        }

        if(JumpState == falling){
            Player.y_pos += GravityForce;
            if(Player.y_pos + Player.size.height >= 191){
                Player.y_pos = 191 - Player.size.height;
                JumpState = grounded;
            }
        }
        else if(JumpState == jumping){
            Player.y_pos -= JumpForce;
            JumpFramesCounter++;
            if(JumpFramesCounter >= JumpFrames){
                JumpFramesCounter = 0;
                JumpState = stationary;
            }
        }
        else if(JumpState == grounded){
            if(pad.pressed & KEY_A)
                JumpState = jumping;
        }
        else if(JumpState == stationary){
            StationaryFramesCounter++;
            if(StationaryFramesCounter >= StationaryFrames){
                StationaryFramesCounter = 0;
                JumpState = falling;
            }
        }

        updateHat(&PlayerHat, Player);
        animateSprite(&Player, 0);
        setSprite(&Player, &oamMain);
        oamUpdate(&oamMain);
    }

    return 0;
}