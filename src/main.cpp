#include <nds.h>
#include <stdio.h>

#include "gfxEvents.h"

//#include <maxmod9.h>
//#include "soundbank.h"
//#include "soundbank_bin.h"

#include "structures.h"

// Include Art
SpriteEntry OAMCopy[128];
#include <Player.h>
#include <PlayerHat.h>

Sprite Player;
Sprite PlayerHat;
BoundingBox PlayerBounds;

int playerHealth = 10;
int enemyHealth = 1;

int main()
{
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

    while(1){
        animateSprite(&Player, 2);
        setSprite(&Player, &oamMain);
        animateSprite(&PlayerHat, 1);
        setSprite(&PlayerHat, &oamMain);
        oamUpdate(&oamMain);
    }

    return 0;
}
