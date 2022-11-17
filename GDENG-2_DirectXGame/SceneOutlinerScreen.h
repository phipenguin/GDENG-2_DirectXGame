#pragma once
#include "AUIScreen.h"

class UIManager;
class SceneOutlinerScreen : public AUIScreen
{
private:
	SceneOutlinerScreen();
	~SceneOutlinerScreen();

	virtual void drawUI() override;

	friend class UIManager;
};