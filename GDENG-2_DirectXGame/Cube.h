#pragma once
#include "AGameObject.h"
#include "VertexBuffer.h"

class Cube : public AGameObject
{
public:
	Cube(string name);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void setAnimationSpeed(float speed);

	VertexBufferPtr getVertexBuffer();
	IndexBufferPtr getIndexBuffer();
	ConstantBufferPtr getConstantBuffer();
	float getTicks();
	float getDeltaTime();
	float getAnimSpeed();

private:
	VertexBufferPtr vertex_buffer;
	IndexBufferPtr index_buffer;
	ConstantBufferPtr constant_buffer;

	//bool isPosGoingPositive = true;
	//bool isScaleGettingBigger = false;
	//bool isCubeWarpingToPlane = true;

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
};