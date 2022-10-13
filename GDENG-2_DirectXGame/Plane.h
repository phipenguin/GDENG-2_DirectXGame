#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

class Plane : public AGameObject
{
public:
	Plane(string name, void* shader_byte_code, size_t size_shader);
	~Plane();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;

	void setAnimationSpeed(float speed);

private:
	VertexBuffer* vertex_buffer;
	ConstantBuffer* constant_buffer;

	float ticks = 0.0f;
	float deltaPosition = 0.0f;
	//float deltaScale = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};