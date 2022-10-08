#pragma once
#include "VertexShader.h"
#include "PixelShader.h"

class AGameObject
{
public:
	virtual void initializeObject(int num, void* shader_byte_code, size_t size_shader);
	virtual void initializeConstantBuffer();
	virtual void destroyObject();

	virtual void drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader);
};