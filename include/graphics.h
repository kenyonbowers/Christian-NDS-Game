#include <nds.h>
#include <stdio.h>
#include "objects.h"

#ifndef GRAPHICS_EVENTS_H_
#define GRAPHICS_EVENTS_H_

void animateSprite(Sprite *sprite, int framesPerAnimation)
{
	int frame = sprite->anim_frame + sprite->state * framesPerAnimation;
	u8* offset = sprite->frame_gfx + frame * sprite->size.width*sprite->size.height;
	dmaCopy(offset, sprite->sprite_gfx_mem, sprite->size.width*sprite->size.height);
}

void initSprite(Sprite *sprite, u8* gfx, OamState *oam)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(oam, sprite->size.text, SpriteColorFormat_256Color);
	sprite->frame_gfx = (u8*)gfx;
}

void setSprite(Sprite *sprite, OamState *oam){
    oamSet(oam, sprite->id, sprite->x_pos, sprite->y_pos, 0, sprite->palette, sprite->size.text, SpriteColorFormat_256Color, sprite->sprite_gfx_mem, -1, false, false, false, false, false);
}

#endif