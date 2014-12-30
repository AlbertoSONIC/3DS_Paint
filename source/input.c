#include "input.h"

//For ctrulib
#include <3ds.h>

//For sprintF
#include <stdio.h>

//Variables
u32 input;
u16 posX;
u16 posY;

void getInput()
{
	//Touch input
	touchPosition myTouchPosition;
	hidTouchRead(&myTouchPosition);

	posX = myTouchPosition.px;
	posY = myTouchPosition.py;

	//HID Input
	hidScanInput();
	input = hidKeysDown();
}