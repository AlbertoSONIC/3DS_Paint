#include <3ds.h>
#include "app.h"
#include "input.h"
#include "rendering.h"

//FPS Counter
u64 tickOld;
int fps;

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
		//Screen flickering workaround
		if (warn == 1 && debug == 1) gspWaitForVBlank();

		//FPS Counter
		if (svcGetSystemTick() >= tickOld + 268123480)
		{
			tickOld = svcGetSystemTick();
			printFPS = fps;
			fps = 0;
		}

		//As nop90 suggested
		getFB();

		//Gets input (keys and touch)
		getInput();

		//Prints the GUI
		printGUI();

		//Do stuff
		app();

		//Exit code
		if (mode==5) break;
			
		// Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();

		fps++;
	}

	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}