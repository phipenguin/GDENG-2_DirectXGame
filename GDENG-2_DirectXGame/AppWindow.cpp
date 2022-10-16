#include "AppWindow.h"
#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Vector3D.h"
#include <Windows.h>
#include <string>

AppWindow* AppWindow::sharedInstance = NULL;

AppWindow::AppWindow()
{
}


AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::getInstance()
{
	return sharedInstance;
}

void AppWindow::initialize()
{
	sharedInstance = new AppWindow();
	sharedInstance->init();
}

void AppWindow::onCreate()
{
	Window::onCreate();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	RenderSystem* renderSystem = RenderSystem::getInstance();
	InputSystem::get()->update();
	//CLEAR THE RENDER TARGET 
	deviceContext->clearRenderTargetColor(this->m_swap_chain,
		0.9f, 0.1f, 0.1f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	deviceContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	renderSystem->drawPlanes(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	renderSystem->drawCubes(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);

	char audio[50]{};
	wchar_t constTowchar[500];
	float v = volume;
	float p = pitch;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	ImGui::Begin("Audio Control");
	ImGui::Text("Audio Source:");
	ImGui::InputText("source input", audio, sizeof(audio), 0, NULL, NULL);

	mbstowcs_s(0, constTowchar, strlen(audio) + 1, audio, _TRUNCATE);
	
	if(!isAudioPlay && strcmp(audio, "Morning Routine.wav") == 0)
	{
		m_audio_system->loadAudioFile(constTowchar);
		m_audio_system->playAudio();
		isAudioPlay = true;
	}

	ImGui::Text(" ");
	ImGui::Text("Volume:");
	ImGui::SliderFloat("volume slider", &v, 0.0f, 200.0f, NULL, 0);

	m_audio_system->setVolume(v);
	volume = v;

	ImGui::Text(" ");
	ImGui::Text("Pitch:");
	ImGui::SliderFloat("pitch slider", &p, 0.0f, 2.0f, NULL, 0);

	if (isAudioPlay)
	{
		m_audio_system->setPitch(p);
		pitch = p;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	m_audio_system->release();
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	GraphicsEngine::destroy();
	RenderSystem::destroy();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(this);
}

void AppWindow::onKeyDown(int key)
{

}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& delta_mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseUp(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& mouse_pos)
{
}

void AppWindow::createGraphicsWindow()
{
	GraphicsEngine::initialize();
	RenderSystem::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	RenderSystem* renderSystem = RenderSystem::getInstance();
	m_swap_chain = graphicsEngine->createSwapChain();
	
	m_audio_system = new AudioSystem();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(this->m_hwnd);
	ImGui_ImplDX11_Init(graphicsEngine->getDevice(), graphicsEngine->getImmediateDeviceContext()->getDeviceContext());
	ImGui::StyleColorsDark();

	m_audio_system->init();

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = graphicsEngine->createVertexShader(shader_byte_code, size_shader);
	
	renderSystem->initializePlanes(shader_byte_code, size_shader);
	renderSystem->initializeCubes(shader_byte_code, size_shader);

	graphicsEngine->releaseCompiledShader();

	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = graphicsEngine->createPixelShader(shader_byte_code, size_shader);
	graphicsEngine->releaseCompiledShader();
}