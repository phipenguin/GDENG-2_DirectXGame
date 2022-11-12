#pragma once
#include <d3d11.h>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);
};