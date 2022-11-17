#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class Plane : public AGameObject
{
public:
	Plane(string name);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void setAnimationSpeed(float speed);

private:
	VertexBufferPtr vertex_buffer;
	IndexBufferPtr index_buffer;
	ConstantBufferPtr constant_buffer;

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};