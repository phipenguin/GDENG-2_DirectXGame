#include "AppWindow.h"
#include "InputSystem.h"

int main()
{
	AppWindow::initialize();
	EngineTime::initialize();
	AppWindow* runningApp = (AppWindow*)AppWindow::getInstance();
	runningApp->createGraphicsWindow();

	while (runningApp->isRun())
	{
		runningApp->broadcast();
	}

	return 0;
}