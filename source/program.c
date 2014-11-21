#include "program.h"
#include "draw.h"

//For ctrulib
#include <3ds\types.h>
#include <3ds\services\hid.h>
#include <3ds\gfx.h>

//For sprintF
#include <stdio.h>

//STATE: 0=start/reset, 2=wait for input, 1=render drawing
int state = 0;

//rev1-2= program revision
int rev1 = 1;
int rev2 = 0;

//Pen color

/*
0 - Eraser
1 - Red
2 - Orange
3 - Yellow
4 - Green
5 - SkyBlue
6 - Blue
7 - Pink
8 - Black
*/
int color = 1;

//Needed to print pixels
int posxy[320][240];
int x = 0;
int y = 0;

//warn becames 1 if the warning prompt is showing up, 2 if it is waiting for a Yes or a No, 0 if it isn't on the screen
int warn = 0;

//Input
u32 input;

//Screen variables
u8* screenBottom = 0;
u8* screenTopLeft = 0;
u8* screenTopRight = 0;

//Variable reset
void variableReset()
{
	warn = 0;
	color = 0;
	for (y = 34; y < 240; y++)
	{
		for (x = 0; x < 320; x++)
		{
			posxy[x][y] = 0;
		}
	}

}


void program()
{
	touchPosition myTouchPosition;

	//Pass pointer to hidTouchRead function which updates values.
	hidTouchRead(&myTouchPosition);

	//Read x cord
	u16 posX = myTouchPosition.px;
	//Read y cord
	u16 posY = myTouchPosition.py;
	hidScanInput();
	input = hidKeysDown();


	//If first boot or time to reset
	if (state == 0)
	{

		clearBottom();
        variableReset();
		printBottomBackgnd();
		printTop();
		printBottomIcon();
		screenRender();
		clearBottom();
		printBottomBackgnd();
		printTop();
		printBottomIcon();
		screenRender();
		
		state = 2;
	}

	if ((posX >= 1 && posX <= 320) && (posY >= 34 && posY <= 240) && warn==0)
	{

		//Plus like dot
		posxy[posX][posY] = color;
        posxy[posX][posY-1] = color;
		posxy[posX][posY+1] = color;
		posxy[posX-1][posY] = color;
		posxy[posX + 1][posY] = color;


		//Square dot
        posxy[posX-1][posY-1] = color;
		posxy[posX+1][posY+1] = color;
        posxy[posX+1][posY-1] = color;
		posxy[posX-1][posY+1] = color;

		//Big dot
		posxy[posX][posY - 2] = color;
		posxy[posX][posY + 2] = color;
		posxy[posX + 2][posY] = color;
		posxy[posX - 2][posY] = color;

		state = 1;
	}
	

	

	//Press DOWN to go home!!!!!!
	if (input & KEY_DOWN && warn == 0)
	{
		aptReturnToMenu();
		renderBottomUi();
	}

	//Changes color/Eraser)
	if (input & KEY_LEFT && warn == 0)
	{
		if (color > 0)
		{
			color = color - 1;
			renderBottomUi();
		}
	}

	if (input & KEY_RIGHT && warn == 0)
	{
		if (color < 7)
		{
			color = color + 1;
			renderBottomUi();

		}
	}
	

	//If active print drawing
	if (state == 1 && warn == 0)
	{
		renderDrawing();
		state = 2;
	}


	//Warning box!!!!

	//Press UP to show it up!
	if (input & KEY_UP && warn == 0)
	{
		warn = 1;
	}

	//Renders warning box
	if (warn == 1)
	{
		printWarning();
		screenRender();
		printWarning();
		screenRender();
		warn = 2;
	}

	//If you tap yes, then it sets state to 0
	if ((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179) && warn == 2)
	{

		state = 0;
	}

	//If you tap No
	if ((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179) && warn == 2)
	{
		renderBottomUi();
		warn = 0;
	}

	//Yes/No using A/B
	if (input & KEY_A && warn == 2)
	{
		state = 0;
	}
	if (input & KEY_B && warn == 2)
	{
		renderBottomUi();
		warn = 0;
	}

}


void printBottomBackgnd()
{
	clearBottom();

	//Prints a white screen!
	drawFillRect(0, 0, 320, 240, 255, 255, 255, screenBottom);

	//Prints the brown toolbar bar!
	drawFillRect(0, 0, 320, 34, 242, 204, 146, screenBottom);
}

void printBottomIcon()
{
	//Prints yellows rectangle by checking if color = red, blue, black or eraser!
	if (color == 0)
	{
		drawFillRect(15, 3, 50, 31, 160, 160, 160, screenBottom);
	}
	if (color == 1)
	{
		drawFillRect(84, 6, 106, 27, 160, 160, 160, screenBottom);
	}
	if (color == 2)
	{
		drawFillRect(118, 6, 140, 27, 160, 160, 160, screenBottom);
	}
	if (color == 3)
	{
		drawFillRect(152, 6, 174, 27, 160, 160, 160, screenBottom);
	}
	if (color == 4)
	{
		drawFillRect(186, 6, 208, 27, 160, 160, 160, screenBottom);
	}
	if (color == 5)
	{
		drawFillRect(220, 6, 242, 27, 160, 160, 160, screenBottom);
	}
	if (color == 6)
	{
		drawFillRect(254, 6, 276, 27, 160, 160, 160, screenBottom);
	}
	if (color == 7)
	{
		drawFillRect(288, 6, 310, 27, 160, 160, 160, screenBottom);
	}

	//Prints the eraser, red part first, then the white one!
	drawFillRect(19, 8, 39, 26, 255, 0, 0, screenBottom);
	drawFillRect(39, 9, 46, 25, 255, 255, 255, screenBottom);

	//Prints 3 color boxes!
	drawFillRect(87, 9, 103, 24, 255, 0, 0, screenBottom);
	drawFillRect(121, 9, 137, 24, 255, 128, 0, screenBottom);
	drawFillRect(155, 9, 171, 24, 255, 255, 0, screenBottom);
	drawFillRect(189, 9, 205, 24, 0, 255, 0, screenBottom);
	drawFillRect(223, 9, 239, 24, 51, 255, 255, screenBottom);
	drawFillRect(257, 9, 273, 24, 0, 0, 255, screenBottom);
	drawFillRect(291, 9, 307, 24, 0, 0, 0, screenBottom);

}

void renderBottomUi()
{
	clearBottom();
	printBottomBackgnd();
	printDrawing();
	printBottomIcon();
	screenRender();
	clearBottom();
	printBottomBackgnd();
	printBottomIcon();
	printDrawing();
	screenRender();
}

void printDrawing()
{
	for (y = 35; y < 240; y++)
	{
		for (x = 0; x < 320; x++)
		{
			if (posxy[x][y] == 0)
			{
				drawPixel(x, y, 255, 255, 255, screenBottom);
			}
			if (posxy[x][y] == 1)
			{
				drawPixel(x, y, 255, 0, 0, screenBottom);
			}
			if (posxy[x][y] == 2)
			{
				drawPixel(x, y, 255, 128, 0, screenBottom);
			}
			if (posxy[x][y] == 3)
			{
				drawPixel(x, y, 255, 255, 0, screenBottom);
			}
			if (posxy[x][y] == 4)
			{
				drawPixel(x, y, 0, 255, 0, screenBottom);
			}
			if (posxy[x][y] == 5)
			{
				drawPixel(x, y, 51, 255, 255, screenBottom);
			}
			if (posxy[x][y] == 6)
			{
				drawPixel(x, y, 0, 0, 255, screenBottom);
			}
			if (posxy[x][y] == 7)
			{
				drawPixel(x, y, 0, 0, 0, screenBottom);
			}


		}
	}

}

void renderDrawing()
{
	printDrawing();
	screenRender();
	printDrawing();
	screenRender();
}

void printWarning()
{
	//Prints a dark grey rectangle!
	drawFillRect(36, 60, 272, 85, 128, 128, 128, screenBottom);

	//Prints a light grey rectangle!
	drawFillRect(36, 85, 272, 189, 160, 160, 160, screenBottom);

	//Prints the buttons!
	drawFillRect(50, 151, 141, 179, 192, 192, 192, screenBottom);
	drawFillRect(166, 151, 257, 179, 192, 192, 192, screenBottom);

	//Prints the text!
	char buffer[100];

	sprintf(buffer, "WARNING!");
	drawString(buffer, 124, 71, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Are you sure that you");
	drawString(buffer, 48, 102, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "want to clear everything?");
	drawString(buffer, 48, 112, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Yes (A)        No (B)");
	drawString(buffer, 66, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);

}


void printTop()
{

		clearTop();

		//Prints the brown background!
		drawFillRect(0, 0, 400, 240, 242, 204, 146, screenTopLeft);
		drawFillRect(0, 0, 400, 240, 242, 204, 146, screenTopRight);

		//Prints the DPAD
		drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopLeft);
		drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopRight);

		drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopLeft);
		drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopRight);

		drawFillRect(0, 129, 17, 134, 242, 204, 146, screenTopLeft);
		drawFillRect(0, 129, 17, 134, 242, 204, 146, screenTopRight);

		drawFillRect(42, 69, 48, 106, 242, 204, 146, screenTopLeft);
		drawFillRect(42, 69, 48, 106, 242, 204, 146, screenTopRight);

		drawFillRect(72, 129, 107, 134, 242, 204, 146, screenTopLeft);
		drawFillRect(72, 129, 107, 134, 242, 204, 146, screenTopRight);

		drawFillRect(42, 159, 48, 196, 242, 204, 146, screenTopLeft);
		drawFillRect(42, 159, 48, 196, 242, 204, 146, screenTopRight);

		//Blue and red rect
		drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopLeft);
		drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopRight);

		drawFillRect(276, 196, 400, 219, 255, 0, 0, screenTopLeft);
		drawFillRect(276, 196, 400, 219, 255, 0, 0, screenTopRight);


		//Text
		char buffer[100];

		sprintf(buffer, "   CLEAN    ");
		drawString(buffer, 1, 31, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 31, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                                  DS Paint");
		drawString(buffer, 1, 46, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 46, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                                 3");
		drawString(buffer, 1, 46, 255, 0, 0, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 46, 255, 0, 0, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                                 Coded by");
		drawString(buffer, 1, 66, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 66, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                                 AlbertoSONIC");
		drawString(buffer, 1, 76, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 76, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                                   Version: %d.%d", rev1, rev2);
		drawString(buffer, 1, 203, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 203, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "   HOME");
		drawString(buffer, 3, 218, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 3, 218, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "   MENU");
		drawString(buffer, 3, 228, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 3, 228, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                CHANGE COLOR");
		drawString(buffer, 1, 121, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 121, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                SELECT ERASER");
		drawString(buffer, 1, 131, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 131, 255, 255, 255, screenTopRight, GFX_LEFT);
	
}


//----------------------------------------- SCREEN RENDERING UTILS -------------------------------------------------

//Screen rendering (both top and bottom)
void screenRender()
{
	gfxFlushBuffers();
	gfxSwapBuffers();
	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL);
	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
}

//Clears the top screen
void clearTop()
{
	screenTopLeft = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	screenTopRight = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	clearScreen(screenTopLeft, GFX_LEFT);
	clearScreen(screenTopRight, GFX_LEFT);
}

//Clears the bottom screen
void clearBottom()
{
	screenBottom = gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL);
	clearScreen(screenBottom, GFX_BOTTOM);
}

