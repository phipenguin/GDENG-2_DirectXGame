#include "RenderSystem.h"
#include "EngineTime.h"
#include "AppWindow.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "VertexBufferTextured.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "ResourceManager.h"
#include "imgui.h"
#include <d3dcompiler.h>
#include <random>
#include <exception>

RenderSystem::RenderSystem()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		throw std::exception("RenderSystem not created successfully");
	}

	m_imm_device_context = std::make_shared<DeviceContext>(m_imm_context, this);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);
}

RenderSystem::~RenderSystem()
{
	//if (m_vs)m_vs->Release();
	//if (m_ps)m_ps->Release();

	//if (m_vsblob)m_vsblob->Release();
	//if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_d3d_device->Release();
}

SwapChainPtr RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;
	try
	{
		sc = std::make_shared<SwapChain>(hwnd, width, height, this);
	}
	catch(...) {}

	return sc;
}

DeviceContextPtr RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

ID3D11Device* RenderSystem::getDirectXDevice()
{
	return this->m_d3d_device;
}

//ID3D11ShaderResourceView* RenderSystem::getTexture()
//{
//	return this->m_texture;
//}

//int RenderSystem::getImageHeight()
//{
//	return this->my_image_height;
//}
//
//int RenderSystem::getImageWidth()
//{
//	return this->my_image_width;
//}

//void RenderSystem::createTextureFromImageFile()
//{
//	ResourceManager* rm = new ResourceManager();
//
//	m_texture = NULL;
//	bool ret = rm->LoadTextureFromImageFile("De_La_Salle_University_Seal.png", &m_texture, &my_image_width, &my_image_height);
//	IM_ASSERT(ret);
//}

VertexBufferPtr RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	VertexBufferPtr vb = nullptr;
	try
	{
		vb = std::make_shared<VertexBuffer>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch(...) {}

	return vb;
}

VertexBufferTexturedPtr RenderSystem::createVertexBufferTextured(void* list_vertices, UINT size_vertex, UINT size_list,
	void* shader_byte_code, size_t size_byte_shader)
{
	VertexBufferTexturedPtr vbt = nullptr;
	try
	{
		vbt = std::make_shared<VertexBufferTextured>(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch(...) {}

	return vbt;
}

IndexBufferPtr RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	IndexBufferPtr id = nullptr;
	try
	{
		id = std::make_shared<IndexBuffer>(list_indices, size_list, this);
	}
	catch(...) {}

	return id;
}

ConstantBufferPtr RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBufferPtr cb = nullptr;
	try
	{
		cb = std::make_shared<ConstantBuffer>(buffer, size_buffer, this);
	}
	catch(...) {}

	return cb;
}

VertexShaderPtr RenderSystem::createVertexShader(void* shader_byte_code, size_t byte_code_size)
{
	VertexShaderPtr vs = nullptr;
	try
	{
		vs = std::make_shared<VertexShader>(shader_byte_code, byte_code_size, this);
	}
	catch(...) {}

	return vs;
}

PixelShaderPtr RenderSystem::createPixelShader(void* shader_byte_code, size_t byte_code_size)
{
	PixelShaderPtr ps = nullptr;
	try
	{
		ps = std::make_shared<PixelShader>(shader_byte_code, byte_code_size, this);
	}
	catch(...) {}

	return ps;
}

bool RenderSystem::compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool RenderSystem::compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void RenderSystem::releaseCompiledShader()
{
	if (m_blob) m_blob->Release();
}

void RenderSystem::initializePlanes()
{
    AppWindow* appWindow = AppWindow::getInstance();

	Plane* plane = new Plane("Plane");
    plane->setAnimationSpeed(2.0f);

 //   //Level 1
 //   if (appWindow->numOfCards == 1 || appWindow->numOfCards == 3 || appWindow->numOfCards == 5)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, 1.0f);

 //       if (appWindow->numOfCards == 1)
 //       	plane->setPosition(Vector3D(-1.6f, 0.0f, 0.0f));
	//	else if (appWindow->numOfCards == 3)
 //   		plane->setPosition(Vector3D(1.6f, 0.0f, 0.0f));
 //       else if (appWindow->numOfCards == 5)
 //   		plane->setPosition(Vector3D(4.8f, 0.0f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
	//if (appWindow->numOfCards == 2 || appWindow->numOfCards == 4 || appWindow->numOfCards == 6)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	if (appWindow->numOfCards == 2)
 //       	plane->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	//	else if (appWindow->numOfCards == 4)
 //   		plane->setPosition(Vector3D(3.2f, 0.0f, 0.0f));
 //       else if (appWindow->numOfCards == 6)
 //   		plane->setPosition(Vector3D(6.4f, 0.0f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
 //   if (appWindow->numOfCards == 7 || appWindow->numOfCards == 8)
 //   {
 //       //plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	if (appWindow->numOfCards == 7)
 //       	plane->setPosition(Vector3D(0.3f, 1.3f, 0.0f));
	//	else if (appWindow->numOfCards == 8)
 //   		plane->setPosition(Vector3D(4.3f, 1.3f, 0.0f));

 //       plane->setScale(Vector3D(2.0f, 0.0f, 0.5f));
 //   }
 //   //Level 2
 //   if (appWindow->numOfCards == 9 || appWindow->numOfCards == 10)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, 1.0f);

 //       if (appWindow->numOfCards == 9)
 //       	plane->setPosition(Vector3D(0.0f, 2.6f, 0.0f));
	//	else if (appWindow->numOfCards == 10)
 //   		plane->setPosition(Vector3D(3.2f, 2.6f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
 //   if (appWindow->numOfCards == 11 || appWindow->numOfCards == 12)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //       if (appWindow->numOfCards == 11)
 //       	plane->setPosition(Vector3D(1.6f, 2.6f, 0.0f));
	//	else if (appWindow->numOfCards == 12)
 //   		plane->setPosition(Vector3D(4.8f, 2.6f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
 //   if (appWindow->numOfCards == 13)
 //   {
 //       //plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	plane->setPosition(Vector3D(2.3f, 3.9f, 0.0f));

 //       plane->setScale(Vector3D(2.0f, 0.0f, 0.5f));
 //   }
 //   //Level 3
 //   if (appWindow->numOfCards == 14)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, 1.0f);

 //   	plane->setPosition(Vector3D(1.6f, 5.1f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
	//if (appWindow->numOfCards == 15)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	plane->setPosition(Vector3D(3.2f, 5.1f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
    plane->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
    plane->setScale(Vector3D(1.0f, 1.0f, 1.0f));
    this->planesList.push_front(plane);
}

void RenderSystem::drawPlanes(int width, int height)
{
    for (auto const& i : planesList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height);
    }
}

void RenderSystem::initializeCubes()
{
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator
	//std::uniform_int_distribution<> distr(0, 15); // define the range

    AppWindow* appWindow = AppWindow::getInstance();

    Cube* cuboid = new Cube("Cube");
    cuboid->setAnimationSpeed(2.0f);

 //   if (appWindow->numOfCubes == 1)
 //   	cuboid->setPosition(Vector3D(0.0f, 0.9f, 0.0f));
 //   else if (appWindow->numOfCubes == 2)
 //       cuboid->setPosition(Vector3D(-1.5f, 2.0f, 0.0f));
	//else if (appWindow->numOfCubes == 3)
 //   	cuboid->setPosition(Vector3D(-1.5f, 3.0f, -2.0f));

	cuboid->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	cuboid->setScale(Vector3D(1.0f, 1.0f, 1.0f));
    this->cubesList.push_front(cuboid);
}

void RenderSystem::initializeTexturedCubes()
{
	AppWindow* appWindow = AppWindow::getInstance();

    TexturedCube* texcuboid = new TexturedCube("Textured Cube");
    texcuboid->setAnimationSpeed(2.0f);

	texcuboid->setPosition(Vector3D(1.0f, 0.0f, 0.0f));
	texcuboid->setScale(Vector3D(1.0f, 1.0f, 1.0f));
    this->cubesList.push_front(texcuboid);
}

void RenderSystem::drawCubes(int width, int height)
{
    //Iterate through the list of cubes
    for (auto const& i : cubesList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height);
    }
}

void RenderSystem::initializeTeapots()
{
	AppWindow* appWindow = AppWindow::getInstance();

    Teapot* teapot = new Teapot("Teapot");
    teapot->setAnimationSpeed(2.0f);

	teapot->setPosition(Vector3D(3.0f, 0.0f, 0.0f));
	teapot->setScale(Vector3D(2.0f, 2.0f, 2.0f));
    this->teapotList.push_front(teapot);
}

void RenderSystem::drawTeapots(int width, int height)
{
    for (auto const& i : teapotList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height);
    }
}