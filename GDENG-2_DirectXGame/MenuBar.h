#pragma once
#include "AUIScreen.h"

class UIManager;
class MenuBar : public AUIScreen
{
private:
	MenuBar();
	~MenuBar();

	virtual void drawUI() override;

	float my_color;

	friend class UIManager;
};