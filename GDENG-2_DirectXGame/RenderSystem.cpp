#include "RenderSystem.h"
#include "EngineTime.h"
#include "AppWindow.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include <d3dcompiler.h>
#include <random>

RenderSystem::RenderSystem()
{
}

bool RenderSystem::init()
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
		return false;
	}

	m_imm_device_context = new DeviceContext(m_imm_context, this);

	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	return true;
}


bool RenderSystem::release()
{
	if (m_vs)m_vs->Release();
	if (m_ps)m_ps->Release();

	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	delete m_imm_device_context;

	m_d3d_device->Release();
	return true;
}

RenderSystem::~RenderSystem()
{
}

SwapChain* RenderSystem::createSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChain* sc = nullptr;
	try
	{
		sc = new SwapChain(hwnd, width, height, this);
	}
	catch(...) {}

	return sc;
}

DeviceContext* RenderSystem::getImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBuffer* RenderSystem::createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader)
{
	VertexBuffer* vb = nullptr;
	try
	{
		vb = new VertexBuffer(list_vertices, size_vertex, size_list, shader_byte_code, size_byte_shader, this);
	}
	catch(...) {}

	return vb;
}

IndexBuffer* RenderSystem::createIndexBuffer(void* list_indices, UINT size_list)
{
	IndexBuffer* id = nullptr;
	try
	{
		id = new IndexBuffer(list_indices, size_list, this);
	}
	catch(...) {}

	return id;
}

ConstantBuffer* RenderSystem::createConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBuffer* cb = nullptr;
	try
	{
		cb = new ConstantBuffer(buffer, size_buffer, this);
	}
	catch(...) {}

	return cb;
}

VertexShader* RenderSystem::createVertexShader(void* shader_byte_code, size_t byte_code_size)
{
	VertexShader* vs = nullptr;
	try
	{
		vs = new VertexShader(shader_byte_code, byte_code_size, this);
	}
	catch(...) {}

	return vs;
}

PixelShader* RenderSystem::createPixelShader(void* shader_byte_code, size_t byte_code_size)
{
	PixelShader* ps = nullptr;
	try
	{
		ps = new PixelShader(shader_byte_code, byte_code_size, this);
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

void RenderSystem::initializePlanes(void* shader_byte_code, size_t size_shader)
{
    AppWindow* appWindow = AppWindow::getInstance();

	Plane* plane = new Plane("Plane", shader_byte_code, size_shader);
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

void RenderSystem::drawPlanes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
    //Iterate through the list of quads
    for (auto const& i : planesList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height, vertex_shader, pixel_shader);
    }
}

void RenderSystem::initializeCubes(void* shader_byte_code, size_t size_shader)
{
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator
	//std::uniform_int_distribution<> distr(0, 15); // define the range

    AppWindow* appWindow = AppWindow::getInstance();

    Cube* cuboid = new Cube("Cube", shader_byte_code, size_shader);
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

void RenderSystem::drawCubes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
    //Iterate through the list of cubes
    for (auto const& i : cubesList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height, vertex_shader, pixel_shader);
    }
}