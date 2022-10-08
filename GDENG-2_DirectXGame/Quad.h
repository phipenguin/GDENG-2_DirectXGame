#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

struct vec3
{
	float x, y, z;
};

// For one position and color only
//struct vertex
//{
//	vec3 position;
//	vec3 color;
//};

// For two positions and colors, animations
struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

__declspec(align(16))
struct constant
{
	float m_angle;
};

class Quad : public AGameObject
{
public:
	void initializeObject(int num, void* shader_byte_code, size_t size_shader) override;
	void destroyObject() override;

	void setAnimSpeed(float minSpeed, float maxSpeed);
	void drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader) override;

private:
	VertexBuffer* vertex_buffer;
	ConstantBuffer* constant_buffer;

	constant cc;

	float decAnimSpeed = 0.0f;
	float incAnimSpeed = 0.0f;
};