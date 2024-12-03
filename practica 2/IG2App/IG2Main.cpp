#include "IG2App.h"

int main(int argc, char* argv[])
{
	IG2App app;

	try
	{
		srand(static_cast<unsigned>(time(NULL)));
		app.initApp();
		app.getRoot()->startRendering();
	}
	catch (Exception& e)
	{
		LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}
	app.closeApp();
	return 0;
}
