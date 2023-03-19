#include <stdio.h>
#include <nds.h>

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

typedef struct
{
    int x_pos;
    int y_pos;

    int animation_frames;

    u16 *sprite_gfx_mem;
    u8 *frame_gfx;

    int state;
    int anim_frame;

    int health;

    int id;
    int priority;
    int palette;

    struct {
        int height = 16;
        int width = 16;
        SpriteSize text = SpriteSize_16x16;
    } size;
} Sprite;

typedef struct
{
	int Xpos;
	int Ypos;

	int SizeX;
	int SizeY;

	int OffsetX;
	int OffsetY;
} BoundingBox;

#endif