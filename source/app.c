#include "app.h"
#include "draw.h"
#include "rendering.h"
#include "input.h"

//For ctrulib
#include <3ds\types.h>
#include <3ds\services\hid.h>
#include <3ds\gfx.h>

//For sprintF
#include <stdio.h>

//For time
#define SECONDS_IN_DAY 86400
#define SECONDS_IN_HOUR 3600
#define SECONDS_IN_MINUTE 60

//STATE: 0=start/reset, 2=wait for input, 1=render drawing
int state = 0;

int mode = 0;

//Debug mode, ON or OFF:
int debug = 0;

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

int rendered = 0;

//warn becames 1 if the warning prompt is showing up, 2 if it is waiting for a Yes or a No, 0 if it isn't on the screen
int warn = 0;

int paintExit = 0;
int appExit = 0;

//Needed to print pixels

int posxy[320][240];
int x = 0;
int y = 0;

int time = 0;

//Debug variables
int debugX;
int debugY;



void app()
{
	//Debug related stuff
	debugX = posX;
	debugY = posY;

	//Do things based off current mode
	if (mode==0)
	{
		//App menu

		//Enter painting
		if ((posX >= 14 && posX <= 302) && (posY >= 68 && posY <= 131))
		{
			mode = 1;
			state = 0; //Cleans the drawing
		}

		//If you tap exit
		if ((posX >= 14 && posX <= 302) && (posY >= 149 && posY <= 212)) warn = 1;


		//If you tap about
		if ((posX >= 6 && posX <= 92) && (posY >= 6 && posY <= 33)) mode = 2;

		//If you tap settings
		if ((posX >= 220 && posX <= 303) && (posY >= 6 && posY <= 33)) mode = 3;


		//WARNING BOX
		//If you tap yes, then it sets mode to 4
		if ((((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A) && warn == 1) mode = 5;

		//If you tap No
		if ((((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B) && warn == 1)	warn = 0;
	}
	else
	{
		if (mode == 1)
		{
			//App paint
			//TODO

		}
		else
		{
			if (mode == 2)
			{
				//App about

				//If you tap close
				if (((posX >= 107 && posX <= 198) && (posY >= 155 && posY <= 183)) || input & KEY_A)
				{
					mode = 0;
         			rendered = 0;
				}

			}
			else
			{
				if (mode == 3)
				{

					//App debug
					//If you tap yes, then it sets debug to 1
					if (((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A)
					{
						debug = 1;
						mode = 0;
					}

					//If you tap No
					if (((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B)
					{
						debug = 0;
						mode = 0;
					}

				}
			}
		}
	}
}


void printGUI()
{
	//print the GUI
    char buffer[100];

	//---------------------------------------------------------------------    TOP SCREEN - TYPES: paint, menu   ------------------------------------------------------------------------------------------
	if (mode == 1) //paint
	{
		//TODO
	}
	else //menu
	{
			//Prints the background!
			drawFillRect(0, 0, 400, 240, 166, 221, 238, screenTopLeft);
			drawFillRect(0, 0, 400, 240, 166, 221, 238, screenTopRight);

			//Prints the DPAD
			drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopLeft);
			drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopRight);

			drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopLeft);
			drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopRight);

			drawFillRect(0, 129, 17, 134, 166, 221, 238, screenTopLeft);
			drawFillRect(0, 129, 17, 134, 166, 221, 238, screenTopRight);

			drawFillRect(42, 69, 48, 106, 166, 221, 238, screenTopLeft);
			drawFillRect(42, 69, 48, 106, 166, 221, 238, screenTopRight);

			drawFillRect(72, 129, 107, 134, 166, 221, 238, screenTopLeft);
			drawFillRect(72, 129, 107, 134, 166, 221, 238, screenTopRight);

			drawFillRect(42, 159, 48, 196, 166, 221, 238, screenTopLeft);
			drawFillRect(42, 159, 48, 196, 166, 221, 238, screenTopRight);

			//Blue rect
			drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopLeft);
			drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopRight);


			//Text
			

			sprintf(buffer, "       ");
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

			sprintf(buffer, "   ");
			drawString(buffer, 3, 218, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 3, 218, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "   ");
			drawString(buffer, 3, 228, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 3, 228, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "                ");
			drawString(buffer, 1, 121, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 1, 121, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "                ");
			drawString(buffer, 1, 131, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 1, 131, 255, 255, 255, screenTopRight, GFX_LEFT);
	}
	
	    //CLOCK - SAME FOR EVERY MODE
		drawFillRect(276, 196, 400, 219, 255, 0, 0, screenTopLeft);
		drawFillRect(276, 196, 400, 219, 255, 0, 0, screenTopRight);

		u64 timeInSeconds = osGetTime() / 1000;
		u64 dayTime = timeInSeconds % SECONDS_IN_DAY;
		sprintf(buffer, "%llu:%llu:%llu", dayTime / SECONDS_IN_HOUR, (dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE, dayTime % SECONDS_IN_MINUTE);

		drawString(buffer, 300, 203, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 300, 203, 255, 255, 255, screenTopRight, GFX_LEFT);
		
		
		//DEBUG - ONLY IF debug==1
		if (debug == 1)
		{
			drawFillRect(79, 163, 264, 239, 0, 0, 0, screenTopLeft);
			drawFillRect(79, 163, 264, 239, 0, 0, 0, screenTopRight);

			sprintf(buffer, "mode= %d      state= %d", mode, state);
			drawString(buffer, 85, 171, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 85, 171, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "color= %d     debug= %d", color, debug);
			drawString(buffer, 85, 181, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 85, 181, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "rendered= %d   warn= %d", rendered, warn);
			drawString(buffer, 85, 191, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 85, 191, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "Touch posX= %d", debugX);
			drawString(buffer, 85, 211, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 85, 211, 255, 255, 255, screenTopRight, GFX_LEFT);

			sprintf(buffer, "Touch posY= %d", debugY);
			drawString(buffer, 85, 221, 255, 255, 255, screenTopLeft, GFX_LEFT);
			drawString(buffer, 85, 221, 255, 255, 255, screenTopRight, GFX_LEFT);

		}



	//---------------------------------------------------------------------    BOTTOM SCREEN - TYPES: paint, menu   ------------------------------------------------------------------------------------------
	if (mode == 1) //paint
	{
		//TODO
	}
	else //menu
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
		drawString(buffer, 30, 16, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "  Debug");
		drawString(buffer, 228, 16, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "START PAINTING");
		drawString(buffer, 98, 81, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Start painting right now!");
		drawString(buffer, 58, 108, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "EXIT 3DS PAINT");
		drawString(buffer, 100, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Go back to homebrew launcher");
		drawString(buffer, 48, 180, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "or 3DS Main Menu");
		drawString(buffer, 89, 192, 255, 255, 255, screenBottom, GFX_BOTTOM);
	}


	//-----------------------------------------------------------------------------------------------   WARNINGS, POPUPS, ABOUT, DEBUG -----------------------------------------------------------------------------------------------
	if (warn == 1)
	{
		//WARNING
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

		sprintf(buffer, "want to do that?");
		drawString(buffer, 48, 112, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Yes (A)        No (B)");
		drawString(buffer, 66, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);
	}
	else if (mode == 2)
	{
		//ABOUT
		//Prints a dark grey rectangle!
		drawFillRect(36, 60, 272, 85, 128, 128, 128, screenBottom);

		//Prints a light grey rectangle!
		drawFillRect(36, 85, 272, 189, 160, 160, 160, screenBottom);

		//Prints the buttons!
		drawFillRect(107, 155, 198, 183, 192, 192, 192, screenBottom);

     	//Prints the text!
		char buffer[100];

		sprintf(buffer, "  ABOUT");
		drawString(buffer, 124, 71, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "App: 3DS Paint");
		drawString(buffer, 41, 102, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Developer: AlbertoSONIC");
		drawString(buffer, 41, 112, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Version: 2.0");
		drawString(buffer, 41, 122, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "      (A) Close");
		drawString(buffer, 71, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);
	}
	else if (mode == 3)
	{
		//DEBUG
		//Prints a dark grey rectangle!
		drawFillRect(36, 60, 272, 85, 128, 128, 128, screenBottom);

		//Prints a light grey rectangle!
		drawFillRect(36, 85, 272, 189, 160, 160, 160, screenBottom);

		//Prints the buttons!
		drawFillRect(50, 151, 141, 179, 192, 192, 192, screenBottom);
		drawFillRect(166, 151, 257, 179, 192, 192, 192, screenBottom);

		//Prints the text!
		char buffer[100];

		sprintf(buffer, "DEBUG:");
		drawString(buffer, 124, 71, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Do you want to enable ");
		drawString(buffer, 48, 102, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "DEBUG mode?");
		drawString(buffer, 48, 112, 255, 255, 255, screenBottom, GFX_BOTTOM);

		sprintf(buffer, "Yes (A)        No (B)");
		drawString(buffer, 66, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);
	}

}




































/*
void menu()
{
	debugX = posX;
	debugY = posY;

	//Mode 0=menu, mode 1=paint, mode 2=about, mode 3=debug

	if (time == 1)
	{
		printTime();
		screenRender();
		printTime();
		screenRender();
	}


	//Menu
	if (mode == 0)
	{

		//Rendering the menu ui
		if (rendered == 0)
		{
			printBottomMenu();
			printTopMenu();
			screenRender();
			printBottomMenu();
			printTopMenu();
			screenRender();
			rendered = 1;
			time = 1;
		}
		//Enter painting
		if ((posX >= 14 && posX <= 302) && (posY >= 68 && posY <= 131))
		{
			mode = 1;
			state = 0;
		}

		//If you tap exit
		if ((posX >= 14 && posX <= 302) && (posY >= 149 && posY <= 212))
		{		
			warn = 1;
			appExit = 1;
			rendered = 0;
		}

		//If you tap about
		if ((posX >= 6 && posX <= 92) && (posY >= 6 && posY <= 33))
		{
			mode = 2;
			rendered = 0;
		}

		//If you tap settings
		if ((posX >= 220 && posX <= 303) && (posY >= 6 && posY <= 33))
		{
			mode = 3;
			rendered = 0;
		}
	}

	//About
	if (mode == 2)
	{
		//Rendering popup
		if (rendered == 0)
		{
			printAbout();
			screenRender();
			printAbout();
			screenRender();
			rendered = 1;
		}
		//If you tap close
		if (((posX >= 107 && posX <= 198) && (posY >= 155 && posY <= 183)) || input & KEY_A)
		{
			mode = 0;

			rendered = 0;
		}
	}

	//Debug
	if (mode == 3)
	{
		//Rendering popup
		if (rendered == 0)
		{
			printDebug();
			screenRender();
			printDebug();
			screenRender();
			rendered = 1;
		}
		//If you tap yes, then it sets debug to 1
		if (((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A)
		{
			debug = 1;
			mode = 0;
			rendered = 0;
		}

		//If you tap No
		if (((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B)
		{
			rendered = 0;
			debug = 0;
			mode = 0;
		}
	}
}


void printBottomMenu()
{
	clearBottom();

	//Prints a background!
	drawFillRect(0, 0, 320, 240, 166, 221, 238, screenBottom);

	//Prints the buttons
	drawFillRect(9, 6, 92, 33, 192, 192, 192, screenBottom);
	drawFillRect(220, 6, 303, 33, 192, 192, 192, screenBottom);

	drawFillRect(14, 68, 302, 131, 51, 153, 255, screenBottom);

	drawFillRect(14, 149, 302, 212, 255, 0, 0, screenBottom);

	//Prints the text

	char buffer[100];

	sprintf(buffer, "About");
	drawString(buffer, 30, 16, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "  Debug");
	drawString(buffer, 228, 16, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "START PAINTING");
	drawString(buffer, 98, 81, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Start painting right now!");
	drawString(buffer, 58, 108, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "EXIT 3DS PAINT");
	drawString(buffer, 100, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Go back to homebrew launcher");
	drawString(buffer, 48, 180, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "or 3DS Main Menu");
	drawString(buffer, 89, 192, 255, 255, 255, screenBottom, GFX_BOTTOM);

}


void printAbout()
{
	//Prints a dark grey rectangle!
	drawFillRect(36, 60, 272, 85, 128, 128, 128, screenBottom);

	//Prints a light grey rectangle!
	drawFillRect(36, 85, 272, 189, 160, 160, 160, screenBottom);

	//Prints the buttons!
	drawFillRect(107, 155, 198, 183, 192, 192, 192, screenBottom);


	//Prints the text!
	char buffer[100];

	sprintf(buffer, "  ABOUT");
	drawString(buffer, 124, 71, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "App: 3DS Paint");
	drawString(buffer, 41, 102, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Developer: AlbertoSONIC");
	drawString(buffer, 41, 112, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Version: 2.0");
	drawString(buffer, 41, 122, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "      (A) Close");
	drawString(buffer, 71, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);

}

void printDebug()
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

	sprintf(buffer, "DEBUG:");
	drawString(buffer, 124, 71, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Do you want to enable ");
	drawString(buffer, 48, 102, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "DEBUG mode?");
	drawString(buffer, 48, 112, 255, 255, 255, screenBottom, GFX_BOTTOM);

	sprintf(buffer, "Yes (A)        No (B)");
	drawString(buffer, 66, 162, 255, 255, 255, screenBottom, GFX_BOTTOM);

}

void printTopMenu()
{

		clearTop();

		//Prints the background!
		drawFillRect(0, 0, 400, 240, 166, 221, 238, screenTopLeft);
		drawFillRect(0, 0, 400, 240, 166, 221, 238, screenTopRight);

		//Prints the DPAD
		drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopLeft);
		drawFillRect(23, 54, 68, 205, 255, 255, 255, screenTopRight);

		drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopLeft);
		drawFillRect(0, 110, 120, 153, 255, 255, 255, screenTopRight);

		drawFillRect(0, 129, 17, 134, 166, 221, 238, screenTopLeft);
		drawFillRect(0, 129, 17, 134, 166, 221, 238, screenTopRight);

		drawFillRect(42, 69, 48, 106, 166, 221, 238, screenTopLeft);
		drawFillRect(42, 69, 48, 106, 166, 221, 238, screenTopRight);

		drawFillRect(72, 129, 107, 134, 166, 221, 238, screenTopLeft);
		drawFillRect(72, 129, 107, 134, 166, 221, 238, screenTopRight);

		drawFillRect(42, 159, 48, 196, 166, 221, 238, screenTopLeft);
		drawFillRect(42, 159, 48, 196, 166, 221, 238, screenTopRight);

		//Blue rect
		drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopLeft);
		drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopRight);

		


		//Text
		char buffer[100];

		sprintf(buffer, "       ");
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

		sprintf(buffer, "   ");
		drawString(buffer, 3, 218, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 3, 218, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "   ");
		drawString(buffer, 3, 228, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 3, 228, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                ");
		drawString(buffer, 1, 121, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 121, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "                ");
		drawString(buffer, 1, 131, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 1, 131, 255, 255, 255, screenTopRight, GFX_LEFT);
	
}

void printTime()
{
	char buffer[100];
	drawFillRect(276, 196, 400, 219, 255, 0, 0, screenTopLeft);
	drawFillRect(276, 196, 400, 219, 255, 0, 0, screenTopRight);

	u64 timeInSeconds = osGetTime() / 1000;
	u64 dayTime = timeInSeconds % SECONDS_IN_DAY;
	sprintf(buffer, "%llu:%llu:%llu", dayTime / SECONDS_IN_HOUR, (dayTime % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE, dayTime % SECONDS_IN_MINUTE);

	drawString(buffer, 300, 203, 255, 255, 255, screenTopLeft, GFX_LEFT);
	drawString(buffer, 300, 203, 255, 255, 255, screenTopRight, GFX_LEFT);


	if (debug == 1)
	{
		drawFillRect(79, 163, 264, 239, 0, 0, 0, screenTopLeft);
		drawFillRect(79, 163, 264, 239, 0, 0, 0, screenTopRight);

		sprintf(buffer, "mode= %d      state= %d", mode, state);
		drawString(buffer, 85, 171, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 85, 171, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "color= %d     debug= %d", color, debug);
		drawString(buffer, 85, 181, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 85, 181, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "rendered= %d   warn= %d", rendered, warn);
		drawString(buffer, 85, 191, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 85, 191, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "Touch posX= %d", debugX);
		drawString(buffer, 85, 211, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 85, 211, 255, 255, 255, screenTopRight, GFX_LEFT);

		sprintf(buffer, "Touch posY= %d", debugY);
		drawString(buffer, 85, 221, 255, 255, 255, screenTopLeft, GFX_LEFT);
		drawString(buffer, 85, 221, 255, 255, 255, screenTopRight, GFX_LEFT);


	}

}

// ************************************************************************************************************************
// Painting section

//Variable reset
void variableReset()
{
	warn = 0;
	color = 0;
	paintExit = 0;
	for (y = 34; y < 240; y++)
	{
		for (x = 0; x < 320; x++)
		{
			posxy[x][y] = 0;
		}
	}

}


void paint()
{
    //Debug stuff
	debugX = posX;
	debugY = posY;

	//Time
	printTime();
	screenRender();
	printTime();
	screenRender();

	//If first boot or time to reset
	if (state == 0)
	{

		clearBottom();
		variableReset();
		printBottomBackgnd();
		printTop();
		printTime();
		printBottomIcon();
		screenRender();
		clearBottom();
		printBottomBackgnd();
		printTop();
		printTime();
		printBottomIcon();
		screenRender();

		state = 2;
	}

	if ((posX >= 0 && posX <= 320) && (posY >= 34 && posY <= 240) && warn == 0)
	{

		//Plus like dot
		posxy[posX][posY] = color;
		posxy[posX][posY - 1] = color;
		posxy[posX][posY + 1] = color;
		posxy[posX - 1][posY] = color;
		posxy[posX + 1][posY] = color;


		//Square dot
		posxy[posX - 1][posY - 1] = color;
		posxy[posX + 1][posY + 1] = color;
		posxy[posX + 1][posY - 1] = color;
		posxy[posX - 1][posY + 1] = color;

		//Big dot
		posxy[posX][posY - 2] = color;
		posxy[posX][posY + 2] = color;
		posxy[posX + 2][posY] = color;
		posxy[posX - 2][posY] = color;

		state = 1;
	}




	//Press DOWN to exit
	if (input & KEY_DOWN && warn == 0)
	{	
		warn = 1;
		paintExit = 1;
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
	if ((((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A) && warn == 2)
	{
		if (paintExit == 1)
		{
			mode = 0;
			variableReset();
			rendered = 0;
		}
		else
		{
			if (appExit == 1) mode = 5;
			else
			{
				variableReset();
				state = 0;
			}
		}

	}

	//If you tap No
	if ((((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B) && warn == 2)
	{
		renderBottomUi();
		warn = 0;
		paintExit = 0;
		appExit = 0;
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

	sprintf(buffer, "want to do that?");
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

	//Blue rect
	drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopLeft);
	drawFillRect(254, 37, 400, 100, 51, 153, 255, screenTopRight);



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

	sprintf(buffer, "   EXIT");
	drawString(buffer, 3, 218, 255, 255, 255, screenTopLeft, GFX_LEFT);
	drawString(buffer, 3, 218, 255, 255, 255, screenTopRight, GFX_LEFT);

	sprintf(buffer, "   ");
	drawString(buffer, 3, 228, 255, 255, 255, screenTopLeft, GFX_LEFT);
	drawString(buffer, 3, 228, 255, 255, 255, screenTopRight, GFX_LEFT);

	sprintf(buffer, "                CHANGE COLOR");
	drawString(buffer, 1, 121, 255, 255, 255, screenTopLeft, GFX_LEFT);
	drawString(buffer, 1, 121, 255, 255, 255, screenTopRight, GFX_LEFT);

	sprintf(buffer, "                SELECT ERASER");
	drawString(buffer, 1, 131, 255, 255, 255, screenTopLeft, GFX_LEFT);
	drawString(buffer, 1, 131, 255, 255, 255, screenTopRight, GFX_LEFT);

}

*/