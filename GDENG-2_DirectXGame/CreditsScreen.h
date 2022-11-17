#pragma once
#include "AUIScreen.h"

class UIManager;
class CreditsScreen : public AUIScreen
{
private:
	CreditsScreen();
	~CreditsScreen();

	virtual void drawUI() override;

	friend class UIManager;
};