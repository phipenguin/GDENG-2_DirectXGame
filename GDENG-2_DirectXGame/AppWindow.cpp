#include "AppWindow.h"
#include "Vector3D.h"
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
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	RenderSystem* renderSystem = RenderSystem::getInstance();
	//CLEAR THE RENDER TARGET 
	deviceContext->clearRenderTargetColor(this->m_swap_chain,
		0.9f, 0.6f, 0.9f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	deviceContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//renderSystem->drawQuads(m_vs, m_ps, rc);
	renderSystem->drawCubes(rc.right - rc.left, rc.bottom - rc.top, m_vs, m_ps);

	//m_cb->update(graphicsEngine->getImmediateDeviceContext(), &cc);

	//graphicsEngine->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	//graphicsEngine->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	////SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	//graphicsEngine->getImmediateDeviceContext()->setVertexShader(m_vs);
	//graphicsEngine->getImmediateDeviceContext()->setPixelShader(m_ps);


	////SET THE VERTICES OF THE TRIANGLE TO DRAW
	//graphicsEngine->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	//// FINALLY DRAW THE TRIANGLE
	//graphicsEngine->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
	//GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleList(m_vb->getSizeVertexList(), 0);
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
	m_swap_chain->release();
	m_vs->release();
	m_ps->release();
	GraphicsEngine::destroy();
	RenderSystem::destroy();
}

void AppWindow::createGraphicsWindow()
{
	GraphicsEngine::initialize();
	RenderSystem::initialize();
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	RenderSystem* renderSystem = RenderSystem::getInstance();
	m_swap_chain = graphicsEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = graphicsEngine->createVertexShader(shader_byte_code, size_shader);

	//renderSystem->initializeQuads(1, shader_byte_code, size_shader);
	//renderSystem->initializeQuads(2, shader_byte_code, size_shader);
	//renderSystem->initializeQuads(3, shader_byte_code, size_shader);
	
	renderSystem->initializeCubes(shader_byte_code, size_shader);

	graphicsEngine->releaseCompiledShader();

	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = graphicsEngine->createPixelShader(shader_byte_code, size_shader);
	graphicsEngine->releaseCompiledShader();
}