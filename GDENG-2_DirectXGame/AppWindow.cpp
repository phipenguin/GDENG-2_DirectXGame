#include "AppWindow.h"
#include <Windows.h>

/*struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};*/

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
	RenderSystem* renderSystem = RenderSystem::getInstance();
	//CLEAR THE RENDER TARGET 
	graphicsEngine->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		1.0f, 0.1f, 0.1f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	graphicsEngine->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	
	//graphicsEngine->getImmediateDeviceContext()->setVertexShader(m_vs);
	//graphicsEngine->getImmediateDeviceContext()->setPixelShader(m_ps);

	renderSystem->drawQuads(m_vs, m_ps);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	//graphicsEngine->getImmediateDeviceContext()->setVertexBuffer(m_vb);

	// FINALLY DRAW THE TRIANGLE
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
	m_swap_chain = graphicsEngine->createSwapChain();

	RECT rc = this->getClientWindowRect();
	m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	/*vertex list[] =
	{
		//X - Y - Z
		//Quadrilateral
		{-0.5f,-0.5f,0.0f,   0,0,0}, // POS1
		{-0.5f,0.5f,0.0f,    1,1,0}, // POS2
		{ 0.5f,-0.5f,0.0f,   0,0,1},// POS2
		{ 0.5f,0.5f,0.0f,    1,1,1}

		//Triangle
		/*{-0.5f,-0.5f,0.0f,	1,0,0}, // POS1
		{ 0,0.5f,0.0f,		0,1,0}, // POS2
		{ 0.5f,-0.5f,0.0f,  0,0,1}, // POS3
	};*/

	//m_vb = graphicsEngine->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);
	
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = graphicsEngine->createVertexShader(shader_byte_code, size_shader);

	RenderSystem::getInstance()->initializeQuads(1, shader_byte_code, size_shader);
	RenderSystem::getInstance()->initializeQuads(2, shader_byte_code, size_shader);
	RenderSystem::getInstance()->initializeQuads(3, shader_byte_code, size_shader);
	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphicsEngine->releaseCompiledShader();


	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = graphicsEngine->createPixelShader(shader_byte_code, size_shader);
	graphicsEngine->releaseCompiledShader();
}