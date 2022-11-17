#include "MenuBar.h"
#include "GraphicsEngine.h"
#include <iostream>

#include "UIManager.h"

MenuBar::MenuBar() : AUIScreen("MenuBar")
{
}

MenuBar::~MenuBar()
{
	AUIScreen::~AUIScreen();
}

void MenuBar::drawUI()
{
	UIManager* uiManager = UIManager::getInstance();

	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits"))
		{
			if (uiManager->getUITable()["CREDITS_SCREEN"]->isWindowOpen == true)
			{
				uiManager->getUITable()["CREDITS_SCREEN"]->isWindowOpen = false;
			}
			else
			{
				uiManager->getUITable()["CREDITS_SCREEN"]->isWindowOpen = true;
			}
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Color Picker"))
	{
		if (uiManager->getUITable()["COLOR_PICKER_SCREEN"]->isWindowOpen == true)
		{
			uiManager->getUITable()["COLOR_PICKER_SCREEN"]->isWindowOpen = false;
		}
		else
		{
			uiManager->getUITable()["COLOR_PICKER_SCREEN"]->isWindowOpen = true;
		}
		ImGui::EndMenu();
	}

	ImGui::EndMainMenuBar();
}