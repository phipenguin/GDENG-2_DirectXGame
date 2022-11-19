#pragma once
#include "AGameObject.h"

class Teapot : public AGameObject
{
public:
	Teapot(string name);
	~Teapot();

	void update(float deltaTime) override;
	void draw(int width, int height) override;

	void setAnimationSpeed(float speed);

private:
	ConstantBufferPtr constant_buffer;

	float ticks = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;

	MeshPtr mesh;
};