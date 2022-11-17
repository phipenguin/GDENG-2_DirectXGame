#pragma once
#include "AUIScreen.h"

class UIManager;
class ColorPickerScreen : public AUIScreen
{
private:
	ColorPickerScreen();
	~ColorPickerScreen();

	virtual void drawUI() override;

	float color;

	friend class UIManager;
};