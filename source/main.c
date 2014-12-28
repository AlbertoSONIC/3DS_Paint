#include <3ds.h>
#include "app.h"
#include "input.h"
#include "rendering.h"

int main()
{
	// Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();

	// Main loop
	while (aptMainLoop())
	{
		//As nop90 suggested
		getFB();

		//Gets input (keys and touch)
		getInput();

		//Prints the GUI
		printGUI();

		//Do stuff
		app();

		//Jumps to the required mode (menu or paint) or exit
		if (input & KEY_START || mode==5)
			break;

		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
	}

	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}