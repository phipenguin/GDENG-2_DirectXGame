#pragma once
#include "Prerequisites.h"
#include "Plane.h"
#include "Cube.h"
#include <list>
#include <d3d11.h>

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();

	SwapChainPtr createSwapChain(HWND hwnd, UINT width, UINT height);
	DeviceContextPtr getImmediateDeviceContext();
	ID3D11Device* getDirectXDevice();

	VertexBufferPtr createVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader);
	IndexBufferPtr createIndexBuffer(void* list_indices, UINT size_list);
	ConstantBufferPtr createConstantBuffer(void* buffer, UINT size_buffer);
	VertexShaderPtr createVertexShader(void* shader_byte_code, size_t byte_code_size);
	PixelShaderPtr createPixelShader(void* shader_byte_code, size_t byte_code_size);

	bool compileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);
	bool compilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size);

	void releaseCompiledShader();


	//For Planes
	void initializePlanes(void* shader_byte_code, size_t size_shader);
	void drawPlanes(int width, int height, VertexShaderPtr vertex_shader, PixelShaderPtr pixel_shader);

	//For Cubes
	void initializeCubes(void* shader_byte_code, size_t size_shader);
	void drawCubes(int width, int height, VertexShaderPtr vertex_shader, PixelShaderPtr pixel_shader);

private:
	DeviceContextPtr m_imm_device_context;

	ID3D11Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;

	IDXGIDevice* m_dxgi_device;
	IDXGIAdapter* m_dxgi_adapter;
	IDXGIFactory* m_dxgi_factory;
	ID3D11DeviceContext* m_imm_context;

	ID3DBlob* m_blob = nullptr;



	//ID3DBlob* m_vsblob = nullptr;
	//ID3DBlob* m_psblob = nullptr;
	//ID3D11VertexShader* m_vs = nullptr;
	//ID3D11PixelShader* m_ps = nullptr;

	std::list<Plane*> planesList;
	std::list<Cube*> cubesList;

	friend class SwapChain;
	friend class VertexBuffer;
	friend class IndexBuffer;
	friend class ConstantBuffer;
	friend class VertexShader;
	friend class PixelShader;
};