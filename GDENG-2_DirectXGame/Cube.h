#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "EngineTime.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

struct cubevertex
{
	Vector3D position;
	Vector3D color;
	Vector3D color1;
};

__declspec(align(16))
struct cubeconstant
{
	Matrix4x4 m_world;
	Matrix4x4 m_view;
	Matrix4x4 m_proj;
	float m_angle;
};

class Cube : public AGameObject
{
	public:
	void initializeObject(int num, void* shader_byte_code, size_t size_shader) override;
	void destroyObject() override;

	void drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect) override;

private:
	void updateObject(RECT client_rect) override;
	void updateObjectPosition() override;
	void updateObjectRotation();
	void updateObjectScale() override;

	VertexBuffer* vertex_buffer;
	IndexBuffer* index_buffer;
	ConstantBuffer* constant_buffer;

	cubeconstant cc;

	Matrix4x4 matrix;
	float deltaPosition;
	float deltaScale;
};