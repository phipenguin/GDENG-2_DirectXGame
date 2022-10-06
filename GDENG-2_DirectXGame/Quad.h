#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 color;
};

class Quad : public AGameObject
{
public:
	void initializeObject(int num, void* shader_byte_code, size_t size_shader) override;
	void destroyObject() override;

	void drawObject(VertexShader* vertexShader, PixelShader* pixelShader) override;
private:
	VertexBuffer* vertexBuffer;
};