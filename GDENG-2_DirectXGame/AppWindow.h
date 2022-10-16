#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "AudioSystem.h"

class AppWindow : public Window
{
public:
	static AppWindow* getInstance();
	static void initialize();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;

	void createGraphicsWindow();

private:
	AppWindow();
	~AppWindow();
	AppWindow(AppWindow const&) {};
	AppWindow& operator=(AppWindow const&) {};
	static AppWindow* sharedInstance;

	SwapChain* m_swap_chain;
	VertexShader* m_vs;
	PixelShader* m_ps;

	AudioSystem* m_audio_system;
};