#include <3ds.h>
#include "menu.h"

int main()
{
	// Initialize services
	srvInit();
	aptInit();
	hidInit(NULL);
	gfxInit();
	//gfxSet3D(true); // uncomment if using stereoscopic 3D

	// Main loop
	while (aptMainLoop())
	{

		// Your code goes here

		
		if (mode == 1)
		{
			paint();
		}
		else
		{
			menu();
		}

            gspWaitForVBlank();
	}




	// Exit services
	gfxExit();
	hidExit();
	aptExit();
	srvExit();
	return 0;
}