#pragma once
#include "Prerequisites.h"
#include "Resource.h"
#include <d3d11.h>
#include <unordered_map>
#include <string>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	//bool LoadTextureFromImageFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
	ResourcePtr createResourceFromFile(const wchar_t* file_path);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t * file_path) = 0;

private:
	std::unordered_map<std::wstring, ResourcePtr> m_map_resources;
};