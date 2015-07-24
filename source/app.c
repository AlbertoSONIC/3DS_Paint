#include <3ds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "draw.h"
#include "input.h"
#include "rendering.h"
#include "gui.h"

//Vars
int state = 0;
int mode = 0;
int save = 0;
int rendered = 0; //Performance Improvements
int sound = 0;
u8 batteryLevel = 5;

//Popups
bool exitPopup = false;
bool clearPopup = false;
bool savePopup = false;
bool debugPopup = false;
bool aboutPopup = false;
bool closePopup = false;

//Debug mode, ON or OFF:
bool debug = false;

//Needed to print pixels
int posxy[320][240];
int x = 0;
int y = 0;

//FPS Counter
int printFPS;

// COLOR TABLE (8 colors, 3-->R G B
int color = 0;
int cTable[8][3]={
	{ 255, 255, 255 }, //0 - Eraser/White
	{ 255, 0, 0 },     //1 - Red
	{ 255, 128, 0 },   //2 - Orange
	{ 255, 255, 0 },   //3 - Yellow
	{ 0, 255, 0 },     //4 - Green
	{ 51, 255, 255 },  //5 - SkyBlue
	{ 0, 0, 255 },     //6 - Blue
	{ 0, 0, 0 }        //7 - Black
};

//Variable reset
void variableReset()
{
	color = 0;
	for (y = 34; y < 240; y++)
	{
		for (x = 0; x < 320; x++)
		{
			posxy[x][y] = 0;
		}
	}
	state = 1;
}


void app()
{
	//Do things based off current mode
	if (mode == 0)
	{
		//App menu

		//Enter painting
		if ((posX >= 14 && posX <= 302) && (posY >= 68 && posY <= 131))
		{
			mode = 1;
			state = 0;
			rendered = 0;
		}

		//If you tap exit
		if ((posX >= 14 && posX <= 302) && (posY >= 149 && posY <= 212)&& !aboutPopup && !debugPopup) exitPopup = true;

		//If you tap about
		if ((posX >= 6 && posX <= 92) && (posY >= 6 && posY <= 33)) aboutPopup = true;

		//If you tap debug
		if ((posX >= 220 && posX <= 303) && (posY >= 6 && posY <= 33)) debugPopup = true;

		//-----> POPUPS FUNCTIONS
		if (exitPopup)
		{
			if (((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A) mode = 5; //If you tap yes
			else if (((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B) exitPopup = false; //If you tap No
		}
		else if (aboutPopup)
		{
			if ((((posX >= 107 && posX <= 198) && (posY >= 155 && posY <= 183)) || input & KEY_A)) aboutPopup = false; //App about, only close button
		}
		else if (debugPopup)
		{
			//App debug
			//If you tap ENABLE, then it sets debug to true
			if (((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A)
			{
				debug = true;
				debugPopup = false;
				mode = 0;
			}
			//If you tap DISABLE
			if (((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B)
			{
				debug = false;
				debugPopup = false;
				mode = 0;
				rendered = 0;
			}
		}
		//-----> POPUP FUNCTIONS ENDED!
	}
	else if (mode == 1)
	{
		//Paint App

		//If init or time to reset ("clean everything")
		if (state == 0) variableReset();

		//Saves the drawn dot into the drawing array
		if ((posX >= 0 && posX <= 320) && (posY >= 34 && posY <= 240) && !closePopup && !clearPopup && !savePopup)
		{
                        if(oldposX != 0 && oldposY != 0 )
                            smoothDrawing(posxy,posX,posY,oldposX,oldposY,color);
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
                        
                        
		}

		//Changes color/Eraser)
		if (input & KEY_LEFT && color > 0)
		{
			color--;
			sound = 1;
		}
		if (input & KEY_RIGHT && color < 7)
		{
			color++;
			sound = 1;
		}

		//Press DOWN to go back to app menu
		if (input & KEY_DOWN && closePopup == false && clearPopup == false && savePopup == false) closePopup = true;

		//Press UP to show it up!
		if (input & KEY_UP && closePopup == false && clearPopup == false && savePopup == false) clearPopup = true;

		//If you tap yes and PaintExit==0, then it sets state to 0, else it exits back to menu
		if ((((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A) && clearPopup == true)
		{
			state = 0;
			clearPopup = false;
		}
		else if ((((posX >= 50 && posX <= 141) && (posY >= 151 && posY <= 179)) || input & KEY_A) && closePopup == true)
		{
			closePopup = false;
			mode = 0;
			variableReset();
			rendered = 0;
		}

		//If you tap No
		if ((((posX >= 167 && posX <= 257) && (posY >= 151 && posY <= 179)) || input & KEY_B) && (closePopup == true || clearPopup == true))
		{
			closePopup = false;
			clearPopup = false;
		}

		//Save drawing to sdcard
		if (input & KEY_SELECT && !closePopup && !clearPopup && !savePopup)
		{
			save = 1;
			savePopup = true;
		}

		//Save popup
		if (savePopup && (((posX >= 107 && posX <= 198) && (posY >= 155 && posY <= 183)) || input & KEY_A)) savePopup = false;
                oldposX=posX;
                oldposY=posY;
	}
}


void printGUI()
{
	//Prints the GUI depending on the active mode
	if (mode == 1) //paint
	{
		if (rendered != 2)
		{
			guiTopPaint();
			rendered++;
		}
		guiBottomPaint(color, cTable, posxy);
	}
	else //menu
	{
		if (rendered != 2)
		{
			guiTopMenu();
			rendered++;
		}
		guiBottomMenu();
	}

	//Prints clock
	guiClock();

	//Popups
	if (exitPopup) guiPopup("EXIT", "Are you sure that you want to exit", "3DS Paint?", " ", "Yes (A)", "No (B)", false);
	else if (clearPopup) guiPopup("CLEAR", "Are you sure that you want to clear", "everything?", "(This action is irreversible)", "Yes (A)", "No (B)", false);
	else if (savePopup) guiPopup("SAVED", "Your drawing has been successfully", "exported to the SDCard! ", "(It's a .bmp image located inside SDCard)", "Close (A)", "", true);
	else if (debugPopup) guiPopup("DEBUG", "Do you want to enable debug features,", "such as FPS counter and other few things?", "(You can deactivate this later)", "Enable (A)", "Disable (B)", false);
	else if (aboutPopup) guiPopup("ABOUT", "App: 3DS Paint", "Dev: AlbertoSONIC (albertosonic.com)", "Version: 2.0", "Close (A)", "", true);
	else if (closePopup) guiPopup("EXIT", "Are you sure that you want to exit?", " ", " ", "Yes (A)", "No (B)", false);

	//Debug
	if (debug) guiDebug(mode, state, color, rendered, sound, printFPS, posX, posY,oldposX,oldposY);
}