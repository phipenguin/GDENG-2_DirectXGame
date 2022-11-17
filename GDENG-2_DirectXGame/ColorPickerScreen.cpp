#include "ColorPickerScreen.h"

ColorPickerScreen::ColorPickerScreen() : AUIScreen("ColorPickerScreen")
{
	isWindowOpen = false;
}

ColorPickerScreen::~ColorPickerScreen()
{
	AUIScreen::~AUIScreen();
}

void ColorPickerScreen::drawUI()
{
	if (isWindowOpen)
	{
		ImGui::Begin("Color Picker Screen");

		ImGui::ColorPicker4("Color", &color);

		ImGui::End();
	}
}