#include "AGameObject.h"

void AGameObject::initializeObject(int num, void* shader_byte_code, size_t size_shader)
{
	AGameObject* obj = new AGameObject();
}

void AGameObject::destroyObject()
{
	delete this;
}

void AGameObject::drawObject(VertexShader* vertexShader, PixelShader* pixelShader)
{
	
}
