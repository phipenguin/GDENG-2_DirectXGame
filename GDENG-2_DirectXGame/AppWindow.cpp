#include "AppWindow.h"
#include "Vector3D.h"
#include "InputSystem.h"
#include "SceneCameraHandler.h"
#include <Windows.h>

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

	InputSystem::initialize();
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::getInstance()->update();

	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	RenderSystem* renderSystem = RenderSystem::getInstance();
	//CLEAR THE RENDER TARGET 
	deviceContext->clearRenderTargetColor(this->m_swap_chain,
		0.9f, 0.6f, 0.9f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	deviceContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	renderSystem->drawPlanes(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	renderSystem->drawCubes(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);
	
	SceneCameraHandler::getInstance()->update();

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	InputSystem::destroy();
	SceneCameraHandler::destroy();
	GraphicsEngine::destroy();
	RenderSystem::destroy();
}

void AppWindow::onFocus()
{
	InputSystem::getInstance()->addListener(this);
}

void AppWindow::onKillFocus()
{
	InputSystem::getInstance()->removeListener(this);
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
	SceneCameraHandler::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	RenderSystem* renderSystem = RenderSystem::getInstance();
	m_swap_chain = graphicsEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

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