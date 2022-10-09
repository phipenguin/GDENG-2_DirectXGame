#include "AppWindow.h"
#include "Vector3D.h"
#include <Windows.h>

//struct vertex
//{
//	Vector3D position;
//	Vector3D position1;
//	Vector3D color;
//	Vector3D color1;
//};

//__declspec(align(16))
//struct constant
//{
//	float m_angle;
//};

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
		0.9f, 0.6f, 0.9f, 1.0f);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	graphicsEngine->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	//unsigned long new_time = 0;
	//if (m_old_time)
	//	new_time = ::GetTickCount() - m_old_time;
	//m_delta_time = new_time / 1000.0f;
	//m_old_time = ::GetTickCount();
	//m_angle += 1.57f * EngineTime::getDeltaTime();
	//constant cc;
	//cc.m_angle = m_angle;

	renderSystem->drawQuads(m_vs, m_ps, rc);

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
	//m_vb->release();
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

	//vertex list[] =
	//{
	//	//X - Y - Z
	//	//Quadrilateral
	//	{-0.5f,-0.5f,0.0f,	-0.32f,-0.11f,0.0f,		0.4,1,0.5,	1,0.4,0.7 }, // POS1
	//	{-0.5f,0.5f,0.0f,	-0.11f,0.78f,0.0f,		0.4,1,0.5,	1,0.4,0.7 }, // POS2
	//	{ 0.5f,-0.5f,0.0f,	 0.75f,-0.73f,0.0f,		0.4,1,0.5,	1,0.4,0.7 }, // POS3
	//	{ 0.5f,0.5f,0.0f,	 0.88f,0.77f,0.0f,		0.4,1,0.5,	1,0.4,0.7 }  // POS4

	//	//Triangle
	//	{-0.5f,-0.5f,0.0f,	1,0,0}, // POS1
	//	{ 0,0.5f,0.0f,		0,1,0}, // POS2
	//	{ 0.5f,-0.5f,0.0f,  0,0,1}, // POS3
	//};

	//m_vb = graphicsEngine->createVertexBuffer();
	//UINT size_list = ARRAYSIZE(list);

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	graphicsEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	m_vs = graphicsEngine->createVertexShader(shader_byte_code, size_shader);

	renderSystem->initializeQuads(1, shader_byte_code, size_shader);
	//renderSystem->initializeQuads(2, shader_byte_code, size_shader);
	//renderSystem->initializeQuads(3, shader_byte_code, size_shader);
	//m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	graphicsEngine->releaseCompiledShader();


	graphicsEngine->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = graphicsEngine->createPixelShader(shader_byte_code, size_shader);
	graphicsEngine->releaseCompiledShader();

	//constant cc;
	//cc.m_angle = 0;
	
	//m_cb = graphicsEngine->createConstantBuffer();
	//m_cb->load(&cc, sizeof(constant));
}