#include "SceneOutlinerScreen.h"

SceneOutlinerScreen::SceneOutlinerScreen() : AUIScreen("SceneOutlinerScreen")
{
}

SceneOutlinerScreen::~SceneOutlinerScreen()
{
	AUIScreen::~AUIScreen();
}

void SceneOutlinerScreen::drawUI()
{
	if (isWindowOpen)
	{
		ImGui::Begin("Scene Outliner");

		ImGui::End();
	}
}