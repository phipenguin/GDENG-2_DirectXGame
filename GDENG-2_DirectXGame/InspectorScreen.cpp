#include "InspectorScreen.h"

InspectorScreen::InspectorScreen() : AUIScreen("InspectorScreen")
{
}

InspectorScreen::~InspectorScreen()
{
	AUIScreen::~AUIScreen();
}

void InspectorScreen::drawUI()
{
	if (isWindowOpen)
	{
		ImGui::Begin("Inspector Window");

		ImGui::End();
	}
}