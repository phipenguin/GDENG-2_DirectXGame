#include "AppWindow.h"



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