#include <stdio.h>
#include <nds.h>

#ifndef OBJECT_STRUCTURES_H_
#define OBJECT_STRUCTURES_H_

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
	int x_pos;
	int y_pos;

	int width;
	int height;

	int x_offset;
	int y_offset;
} BoundingBox;

bool checkCollision(BoundingBox r1, BoundingBox r2){
	return(r1.x_pos < r2.x_pos + r2.width && r1.x_pos + r1.width > r2.x_pos && r1.y_pos < r2.y_pos + r2.height && r1.height + r1.height > r2.y_pos);
}

#endif