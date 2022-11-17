#include "UIManager.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "MenuBar.h"
#include "CreditsScreen.h"
#include "ColorPickerScreen.h"
#include "InspectorScreen.h"
#include "SceneOutlinerScreen.h"

UIManager* UIManager::sharedInstance = nullptr;

UIManager* UIManager::getInstance()
{
	return sharedInstance;
}

void UIManager::initialize(HWND hwnd)
{
	sharedInstance = new UIManager(hwnd);
}

void UIManager::destroy()
{
	delete sharedInstance;
}

void UIManager::drawAllUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (int i = 0; i < this->uiList.size(); i++)
	{
		this->uiList[i]->drawUI();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

UIManager::UITable UIManager::getUITable()
{
	return this->uiTable;
}

UIManager::UIManager(HWND hwnd)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	RenderSystem* renderSystem = graphicsEngine->getRenderSystem();

	//Setup ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX11_Init(renderSystem->getDirectXDevice(), renderSystem->getImmediateDeviceContext()->getContext());
	ImGui::StyleColorsDark();

	UINames uiNames;
	MenuBar* menuBar = new MenuBar();
	this->uiTable[uiNames.MENU_BAR] = menuBar;
	this->uiList.push_back(menuBar);

	CreditsScreen* creditsScreen = new CreditsScreen();
	this->uiTable[uiNames.CREDITS_SCREEN] = creditsScreen;
	this->uiList.push_back(creditsScreen);

	ColorPickerScreen* colorPickerScreen = new ColorPickerScreen();
	this->uiTable[uiNames.COLOR_PICKER_SCREEN] = colorPickerScreen;
	this->uiList.push_back(colorPickerScreen);

	InspectorScreen* inspectorScreen = new InspectorScreen();
	this->uiTable[uiNames.INSPECTOR_SCREEN] = inspectorScreen;
	this->uiList.push_back(inspectorScreen);

	SceneOutlinerScreen* sceneOutlinerScreen = new SceneOutlinerScreen();
	this->uiTable[uiNames.SCENE_OUTLINER_SCREEN] = sceneOutlinerScreen;
	this->uiList.push_back(sceneOutlinerScreen);
}

UIManager::~UIManager()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}