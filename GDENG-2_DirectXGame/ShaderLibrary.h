#pragma once
#include "Prerequisites.h"
#include <iostream>
#include <unordered_map>
#include <string>

class VertexShader;
class PixelShader;

class ShaderNames
{
public:
	typedef std::wstring String;
	//vertex shader names
	const String BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const String TEXTURED_VERTEX_SHADER_NAME = L"TexturedVertexShader.hlsl";
	const String VERTEX_MESH_LAYOUT_SHADER_NAME = L"VertexMeshLayoutShader.hlsl";

	//pixel shader names
	const String BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const String TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
};

class ShaderLibrary
{
public:
	class ShaderData
	{
	public:
		void* shaderByteCode = NULL;
		size_t sizeShader = 0;
	};

	typedef std::wstring String;
	typedef std::unordered_map<String, VertexShaderPtr> VertexShaderTable;
	typedef std::unordered_map<String, PixelShaderPtr> PixelShaderTable;

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	//since shader byte code gets dereferenced for some reason if stored in a hash table. request manually.
	void requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader);
	VertexShaderPtr getVertexShader(String vertexShaderName);
	PixelShaderPtr getPixelShader(String pixelShaderName);

	void getVertexMeshLayoutShaderByteCodeAndSize(void** byte_code, size_t* size);

private:
	ShaderLibrary();
	~ShaderLibrary();
	ShaderLibrary(ShaderLibrary const&) {};
	ShaderLibrary& operator=(ShaderLibrary const&) {};
	static ShaderLibrary* sharedInstance;

	VertexShaderTable activeVertexShaders;
	PixelShaderTable activePixelShaders;

	unsigned char m_mesh_layout_byte_code[1024];
	size_t m_mesh_layout_size = 0;
};