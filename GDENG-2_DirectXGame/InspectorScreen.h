#pragma once
#include "AUIScreen.h"

class UIManager;
class InspectorScreen : public AUIScreen
{
private:
	InspectorScreen();
	~InspectorScreen();

	virtual void drawUI() override;

	friend class UIManager;
};