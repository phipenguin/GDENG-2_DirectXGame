#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Cube : public AGameObject
{
public:
	Cube(string name, void* shader_byte_code, size_t size_shader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShaderPtr vertex_shader, PixelShaderPtr pixel_shader) override;

	void setAnimationSpeed(float speed);

private:

	VertexBufferPtr vertex_buffer;
	IndexBufferPtr index_buffer;
	ConstantBufferPtr constant_buffer;

	//bool isPosGoingPositive = true;
	//bool isScaleGettingBigger = false;
	//bool isCubeWarpingToPlane = true;

	float ticks = 0.0f;
	float deltaPosition = 0.0f;
	//float deltaScale = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;

	float incAnimSpeed = 0.0f;
	float decAnimSpeed = 0.0f;
};