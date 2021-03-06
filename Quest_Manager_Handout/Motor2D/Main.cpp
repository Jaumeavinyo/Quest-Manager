#include <stdlib.h>

#include "Defs.h"
#include "Log.h"
#include "App.h"

// This is needed here because SDL redefines main function
// do not add any other libraries here, instead put them in their modules
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )

#include "Brofiler/Brofiler.h"
#pragma comment( lib, "Brofiler/ProfilerCore32.lib" )

enum MainState
{
	CREATE = 1,
	AWAKE,
	START,
	LOOP,
	CLEAN,
	FAIL,
	EXIT
};

App* myApp = NULL;

int main(int argc, char* args[])
{
	LOG("Engine starting ... %d");

	MainState state = MainState::CREATE;
	int result = EXIT_FAILURE;

	while(state != EXIT)
	{
		switch(state)
		{

			// Allocate the engine --------------------------------------------
			case CREATE:
			LOG("CREATION PHASE ===============================");

			myApp = new App(argc, args);

			if(myApp != NULL)
				state = AWAKE;
			else
				state = FAIL;

			break;

			// Awake all modules -----------------------------------------------
			case AWAKE:
			LOG("AWAKE PHASE ===============================");
			if(myApp->Awake() == true)
				state = START;
			else
			{
				LOG("ERROR: Awake failed");
				state = FAIL;
			}

			break;

			// Call all modules before first frame  ----------------------------
			case START:
			LOG("START PHASE ===============================");
			if(myApp->Start() == true)
			{
				state = LOOP;
				LOG("UPDATE PHASE ===============================");
			}
			else
			{
				state = FAIL;
				LOG("ERROR: Start failed");
			}
			break;

			// Loop all modules until we are asked to leave ---------------------
			case LOOP: 
			{

				BROFILER_FRAME("MainLoop");
				if (myApp->Update() == false)
					state = CLEAN;
			}
			break;

			// Cleanup allocated memory -----------------------------------------
			case CLEAN:
			LOG("CLEANUP PHASE ===============================");
			if(myApp->CleanUp() == true)
			{
				RELEASE(myApp);
				result = EXIT_SUCCESS;
				state = EXIT;
			}
			else
				state = FAIL;

			break;

			// Exit with errors and shame ---------------------------------------
			case FAIL:
			LOG("Exiting with errors :(");
			result = EXIT_FAILURE;
			state = EXIT;
			break;
		}
	}

	LOG("... Bye! :)\n");

	// Dump memory leaks
	return result;
}