#include "AGameObject.h"

void AGameObject::initializeObject(int num, void* shader_byte_code, size_t size_shader)
{
}

void AGameObject::initializeConstantBuffer()
{
}

void AGameObject::destroyObject()
{
	delete this;
}

void AGameObject::updateObject(RECT client_rect)
{
}

void AGameObject::updateObjectPosition()
{
}

void AGameObject::updateObjectScale()
{
}

void AGameObject::drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect)
{
}
