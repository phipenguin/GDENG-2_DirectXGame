#pragma once
#include "Window.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "AudioSystem.h"
#include "ImGui\\imgui.h"
#include "ImGui\\imgui_impl_win32.h"
#include "ImGui\\imgui_impl_dx11.h"


class AppWindow : public Window, public InputListener
{
public:
	static AppWindow* getInstance();
	static void initialize();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;

	// Inherited via InputListener
	virtual void onKeyDown(int key) override;
	virtual void onKeyUp(int key) override;
	virtual void onMouseMove(const Point& delta_mouse_pos) override;

	virtual void onLeftMouseDown(const Point& mouse_pos) override;
	virtual void onLeftMouseUp(const Point& mouse_pos) override;
	virtual void onRightMouseDown(const Point& mouse_pos) override;
	virtual void onRightMouseUp(const Point& mouse_pos) override;

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
	bool isAudioPlay = false;
	float volume = 100.0f;
	float pitch = 1.0f;
};