#include <nds.h>
#include <stdio.h>

#include "graphics.h"
#include "objects.h"
#include "input.h"

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
int GravityForce = 1;
bool OnGround = false;

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
    Input input;

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

    while (1)
    {
        swiWaitForVBlank();

        input = getInput();

        if(input.held & KEY_LEFT){
			if(Player.x_pos > 0){
                Player.x_pos -= PlayerSpeed;
            }
		}
        else if (input.held & KEY_RIGHT){
            if (Player.x_pos < 256 - 16){
                Player.x_pos += PlayerSpeed;
            }
        }

        if(!OnGround){
            Player.y_pos += GravityForce;
        }

        updateHat(&PlayerHat, Player);
        animateSprite(&Player, 0);
        setSprite(&Player, &oamMain);
        oamUpdate(&oamMain);
    }

    return 0;
}