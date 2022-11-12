#include "CreditsScreen.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"

CreditsScreen::CreditsScreen() : AUIScreen("Credits Screen")
{
	
}

CreditsScreen::~CreditsScreen()
{
	AUIScreen::~AUIScreen();
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");

	ImGui::Image((void*)GraphicsEngine::getInstance()->getRenderSystem()->getTexture(), ImVec2(GraphicsEngine::getInstance()->getRenderSystem()->getImageWidth(), GraphicsEngine::getInstance()->getRenderSystem()->getImageHeight()));
	ImGui::Text("About:");
	ImGui::BulletText("Scene Editor Ver 1.0");
	ImGui::BulletText("Developer: Paul Bradley U. Ong");
	ImGui::Text("");
	ImGui::Text("Acknowledgements:");
	ImGui::BulletText("Sir Neil DelGallego");
	ImGui::BulletText("Pardcode (https://www.youtube.com/c/PardCode)");
	ImGui::BulletText("DearImGui (https://github.com/ocornut/imgui)");

	ImGui::End();
}