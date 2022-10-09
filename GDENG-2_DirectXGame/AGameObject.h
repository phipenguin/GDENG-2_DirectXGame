#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "Matrix4x4.h"

class AGameObject
{
public:
	virtual void initializeObject(int num, void* shader_byte_code, size_t size_shader);
	virtual void initializeConstantBuffer();
	virtual void destroyObject();

	virtual void drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect);

private:
	virtual void updateObject(RECT client_rect);
	virtual void updateObjectPosition();
	virtual void updateObjectScale();
};