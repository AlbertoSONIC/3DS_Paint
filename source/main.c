#include "main.h"
#include "menu.h"
/* New ctrulib */
#include <3ds.h>


int main()
{
	//Grab the status of the app (running, suspending, sleeping, exiting)
	APP_STATUS status;

	//Initialize 3ds services
	srvInit();
	fsInit();
	aptInit();
	gfxInit();
	hidInit(NULL);
	//Setup event handler to listen for changes in status
	aptSetupEventHandler();


	while ((status = aptGetStatus()) != APP_EXITING)
	{

		if (status == APP_RUNNING)
		{

			//If the app is currently in the forground running, execute the program.
			if (mode == 1)
			{
				paint();
			}
			else
			{
				menu();
			}
		}
		else if (status == APP_SUSPENDING)
		{
			//If the app is currently suspended in the background, return to the home menu.
			aptReturnToMenu();
		}
		else if (status == APP_SLEEPMODE)
		{
			//If the app is currently suspended in sleep mode, wait.
			aptWaitStatusEvent();
		}

		//Wait for GPU
		gspWaitForVBlank();

	}

	//Close all opened services.
	hidExit();
	gfxExit();
	aptExit();
	srvExit();
	//Kill the process.
	svcExitProcess();
	return 0;
}