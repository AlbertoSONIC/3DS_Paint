#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gui.h"
#include "draw.h"
#include "rendering.h"
#define ctablesize 3
#define posxysize 240

//For time
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60
int time = 0;

//Vars
int var1 = 240;

//Needed to print pixels / gui
int guix = 0;
int guiy = 0;
int guix1;
int guix2;
int box;

char buffer[100];


void guiTopPaint()
{
	//Prints the brown background!
	drawFillRect(0, 0, 399, 239, 242, 204, 146, screenTopLeft);
	//Prints the DPAD
	drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopLeft);
	drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopLeft);
	drawFillRect(0, 129, 17, 134, 242, 204, 146, screenTopLeft);
	drawFillRect(42, 69, 48, 106, 242, 204, 146, screenTopLeft);
	drawFillRect(72, 129, 107, 134, 242, 204, 146, screenTopLeft);
	drawFillRect(42, 159, 48, 196, 242, 204, 146, screenTopLeft);
	//Blue rect
	drawFillRect(254, 37, 399, 100, 51, 153, 255, screenTopLeft);
	//Green rect (save)
	drawFillRect(257, 138, 399, 168, 69, 206, 48, screenTopLeft);


	//Text
	sprintf(buffer, "CLEAN");
	gfxDrawText(GFX_TOP, GFX_RIGHT, NULL, buffer, 27, 240 - fontDefault.height * 3);

	sprintf(buffer, "3DS Paint");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 230 - fontDefault.height * 3);

	sprintf(buffer, "Coded by");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 240 - fontDefault.height * 5);

	sprintf(buffer, "AlbertoSONIC");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 240 - fontDefault.height * 6);

	sprintf(buffer, "          EXIT");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 3, 240 - fontDefault.height * 14);

	sprintf(buffer, "CHANGE COLOR");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 130, 235 - fontDefault.height * 8);

	sprintf(buffer, "SELECT ERASER");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 130, 235 - fontDefault.height * 9);

	sprintf(buffer, "Press SELECT to export");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 245 - fontDefault.height * 10);

	sprintf(buffer, "your drawing to SDCARD");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 248 - fontDefault.height * 11);
}


void guiTopMenu()
{
	//Prints the background!
	drawFillRect(0, 0, 399, 239, 166, 221, 238, screenTopLeft);
	//Prints the DPAD
	drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopLeft);
	drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopLeft);
	drawFillRect(0, 129, 17, 134, 166, 221, 238, screenTopLeft);
	drawFillRect(42, 69, 48, 106, 166, 221, 238, screenTopLeft);
	drawFillRect(72, 129, 107, 134, 166, 221, 238, screenTopLeft);
	drawFillRect(42, 159, 48, 196, 166, 221, 238, screenTopLeft);
	//Blue rect
	drawFillRect(254, 37, 399, 100, 51, 153, 255, screenTopLeft);

	//Text
	sprintf(buffer, "3DS Paint");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 230 - fontDefault.height * 3);

	sprintf(buffer, "Coded by");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 240 - fontDefault.height * 5);

	sprintf(buffer, "AlbertoSONIC");
	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 265, 240 - fontDefault.height * 6);

}

void guiBottomPaint(int color, int cTable[][ctablesize], int posxy[][posxysize])
{
	//Prints a white screen!
	drawFillRect(0, 0, 320, 240, 255, 255, 255, screenBottom);

	//Prints the brown toolbar bar!
	drawFillRect(0, 0, 320, 34, 242, 204, 146, screenBottom);

	//Highlights the selected color
	if (color == 0)	drawFillRect(15, 3, 50, 31, 160, 160, 160, screenBottom);
	if (color == 1)	drawFillRect(84, 6, 106, 27, 160, 160, 160, screenBottom);
	if (color == 2) drawFillRect(118, 6, 140, 27, 160, 160, 160, screenBottom);
	if (color == 3)	drawFillRect(152, 6, 174, 27, 160, 160, 160, screenBottom);
	if (color == 4) drawFillRect(186, 6, 208, 27, 160, 160, 160, screenBottom);
	if (color == 5) drawFillRect(220, 6, 242, 27, 160, 160, 160, screenBottom);
	if (color == 6) drawFillRect(254, 6, 276, 27, 160, 160, 160, screenBottom);
	if (color == 7) drawFillRect(288, 6, 310, 27, 160, 160, 160, screenBottom);

	//Prints the eraser, red part first, then the white one!
	drawFillRect(19, 8, 39, 26, 255, 0, 0, screenBottom);
	drawFillRect(39, 9, 46, 25, 255, 255, 255, screenBottom);

	//Prints 8 color boxes!
	guix1 = 87;
	guix2 = 103;
	for (box = 1; box < 8; box++)
	{
		drawFillRect(guix1, 9, guix2, 24, cTable[box][0], cTable[box][1], cTable[box][2], screenBottom);
		guix1 = guix1 + 34;
		guix2 = guix2 + 34;
	}

	//Print drawing
	for (guiy = 35; guiy < 240; guiy++)
	{
		for (guix = 0; guix < 320; guix++)
		{
			drawPixel(guix, guiy, cTable[posxy[guix][guiy]][0], cTable[posxy[guix][guiy]][1], cTable[posxy[guix][guiy]][2], screenBottom);
		}
	}
}

void guiBottomMenu()
{
	//Prints a background!
	drawFillRect(0, 0, 320, 240, 166, 221, 238, screenBottom);

	//Prints the buttons
	drawFillRect(9, 6, 92, 33, 192, 192, 192, screenBottom);
	drawFillRect(220, 6, 303, 33, 192, 192, 192, screenBottom);
	drawFillRect(14, 68, 302, 131, 51, 153, 255, screenBottom);
	drawFillRect(14, 149, 302, 212, 255, 0, 0, screenBottom);

	//Prints the text
	sprintf(buffer, "About");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 30, 245- fontDefault.height * 2);

	sprintf(buffer, "  Debug");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 235, 245 - fontDefault.height * 2);

	sprintf(buffer, "START PAINTING");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 108, 240 - fontDefault.height * 6);

	sprintf(buffer, "Start painting right now!");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 88, 240 - fontDefault.height * 7);

	sprintf(buffer, "EXIT 3DS PAINT");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 110, 240 - fontDefault.height * 11);

	sprintf(buffer, "Go back to homebrew launcher");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 70, 240 - fontDefault.height * 12);

	sprintf(buffer, "or 3DS Main Menu");
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, buffer, 100, 240 - fontDefault.height * 13);
}

void guiClock()
{
	//CLOCK
	drawFillRect(276, 196, 399, 219, 255, 0, 0, screenTopLeft);

	u64 timeInSeconds = osGetTime() / 1000;
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY;
	sprintf(buffer, "%llu:%llu:%llu", dayTime / SECONDS_IN_HOUR, (dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE, dayTime % SECONDS_IN_MINUTE);

	gfxDrawText(GFX_TOP, GFX_LEFT, NULL, buffer, 300, 248 - fontDefault.height * 14);
}

void guiPopup(char* title, char* line1, char* line2, char* line3, char* button1, char* button2, bool closeonly)
{
	//Prints a dark grey rectangle!
	drawFillRect(36, 60, 272, 85, 128, 128, 128, screenBottom);
	//Prints a light grey rectangle!
	drawFillRect(36, 85, 272, 189, 160, 160, 160, screenBottom);
	//Prints text
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, title, 124, 240 - fontDefault.height * 5);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, line1, 50, 245 - fontDefault.height * 7);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, line2, 50, 245 - fontDefault.height * 8);
	gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, line3, 50, 245 - fontDefault.height * 9);
    //Prints the buttons!
	if (closeonly)
	{
        drawFillRect(107, 155, 198, 183, 192, 192, 192, screenBottom);
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, button1, 130, 240 - fontDefault.height * 11);
	}
	else
	{
		drawFillRect(50, 151, 141, 179, 192, 192, 192, screenBottom);
	    drawFillRect(166, 151, 257, 179, 192, 192, 192, screenBottom);
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, button1, 60, 240 - fontDefault.height * 11);
		gfxDrawText(GFX_BOTTOM, GFX_LEFT, NULL, button2, 180, 240 - fontDefault.height * 11);
	}	
}

void guiDebug(int mode, int state, int color, int rendered, int printFPS, int posX, int posY)
{
	//Todo
	drawFillRect(79, 163, 250, 239, 0, 0, 0, screenTopLeft);
}