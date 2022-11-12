#include "MenuScreen.h"
#include "GraphicsEngine.h"
#include <iostream>

MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{
}

MenuScreen::~MenuScreen()
{
	AUIScreen::~AUIScreen();
}

void MenuScreen::drawUI()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits"))
		{
			
		}
		ImGui::EndMenu();
	}
	ImGui::EndMainMenuBar();

	ImGui::Begin("Color Picker Screen");
	ImGui::ColorPicker4("Color", &my_color);
	ImGui::End();
}