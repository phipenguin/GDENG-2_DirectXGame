#include "MenuScreen.h"

MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{
}

MenuScreen::~MenuScreen()
{
	AUIScreen::~AUIScreen();
}

void MenuScreen::drawUI()
{
	ImGui::Begin("Menu Screen");

	ImGui::End();
}