#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"
#include "Vector3D.h"

struct quadvertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct quadconstant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

class Quad : public AGameObject
{
public:
	void initializeObject(int num, void* shader_byte_code, size_t size_shader) override;
	void destroyObject() override;

	//void setAnimSpeed(float minSpeed, float maxSpeed);
	void drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect) override;

private:
	void updateObject(RECT client_rect) override;
	void updateObjectPosition() override;
	void updateObjectScale() override;

	VertexBuffer* vertex_buffer;
	ConstantBuffer* constant_buffer;

	quadconstant cc;

	//float decAnimSpeed = 0.0f;
	//float incAnimSpeed = 0.0f;

	Matrix4x4 matrix;
	float deltaPosition;
	float deltaScale;
};