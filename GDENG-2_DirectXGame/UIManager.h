#pragma once
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

class UINames
{
public:
	const String MENU_BAR = "MENU_BAR";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLOR_PICKER_SCREEN = "COLOR_PICKER_SCREEN";
	const String INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const String SCENE_OUTLINER_SCREEN = "SCENE_OUTLINER_SCREEN";
};

class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND hwnd);
	static void destroy();

	void drawAllUI();

	UITable getUITable();

	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND hwnd);
	~UIManager();
	UIManager(UIManager const&) {};
	UIManager& operator=(UIManager const&) {};
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};