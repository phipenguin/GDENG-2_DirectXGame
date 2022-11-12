#pragma once
#include "AUIScreen.h"

class UIManager;
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;

	float my_color;

	friend class UIManager;
};