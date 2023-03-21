#include <nds.h>
#include <stdio.h>

#ifndef INPUT_H_
#define INPUT_H_

typedef struct
{
	int pressed;
    int held;
	int released;
    touchPosition touch;
} Input;

Input getInput(){
    scanKeys();
    Input pad;
    touchRead(&pad.touch);
    pad.pressed = keysDown();
	pad.held = keysHeld();
	pad.released = keysUp();

    return pad;    
}

#endif