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
	RenderSystem* renderSystem = graphicsEngine->getRenderSystem();
	DeviceContext* deviceContext = graphicsEngine->getRenderSystem()->getImmediateDeviceContext();
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
	delete m_swap_chain;
	delete m_vs;
	delete m_ps;
	InputSystem::destroy();
	SceneCameraHandler::destroy();
	GraphicsEngine::destroy();
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
	SceneCameraHandler::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	RenderSystem* renderSystem = graphicsEngine->getRenderSystem();

	RECT rc = this->getClientWindowRect();
	m_swap_chain = renderSystem->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	renderSystem->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = renderSystem->createVertexShader(shader_byte_code, size_shader);

	//for (int i = 0; i < 15; i++)
	//{
	//	numOfCards++;
	//	renderSystem->initializePlanes(shader_byte_code, size_shader);
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	numOfCubes++;
	//	renderSystem->initializeCubes(shader_byte_code, size_shader);
	//}

	renderSystem->initializePlanes(shader_byte_code, size_shader);
	renderSystem->initializeCubes(shader_byte_code, size_shader);

	renderSystem->releaseCompiledShader();

	renderSystem->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = renderSystem->createPixelShader(shader_byte_code, size_shader);
	renderSystem->releaseCompiledShader();
}