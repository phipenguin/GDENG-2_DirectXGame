#include "Quad.h"

void Quad::initializeObject(int num, void* shader_byte_code, size_t size_shader)
{
	AGameObject::initializeObject(num, shader_byte_code, size_shader);
	vertexBuffer = GraphicsEngine::getInstance()->createVertexBuffer();

	vertex list1[] =
	{
		//X - Y - Z
		//Quadrilateral
		{-0.7f,0.6f,0.0f,   1,1,1},
		{-0.3f,0.9f,0.0f,   1,1,1},
		{ 0.7f,0.6f,0.0f,	1,1,1},
		{ 0.3f,0.9f,0.0f,   1,1,1}
	};

	vertex list2[] =
	{
		{-0.5f,-0.5f,0.0f,   0,0,0},
		{-0.5f,0.5f,0.0f,    0,0,0},
		{ 0.5f,-0.5f,0.0f,   0,0,0},
		{ 0.5f,0.5f,0.0f,    0,0,0}
	};

	vertex list3[] =
	{
		{-0.3f,-0.9f,0.0f,   0.7,0.7,0},
		{-0.7f,-0.6f,0.0f,   0.7,0.7,0},
		{ 0.7f,-0.9f,0.0f,   0.7,0.7,0},
		{ 0.3f,-0.6f,0.0f,   0.7,0.7,0}
	};

	UINT size_list = ARRAYSIZE(list1);

	if (num == 1)
		vertexBuffer->load(list1, sizeof(vertex), size_list, shader_byte_code, size_shader);
	else if (num == 2)
		vertexBuffer->load(list2, sizeof(vertex), size_list, shader_byte_code, size_shader);
	else if (num == 3)
		vertexBuffer->load(list3, sizeof(vertex), size_list, shader_byte_code, size_shader);
}

void Quad::destroyObject()
{
	AGameObject::destroyObject();
}

void Quad::drawObject(VertexShader* vertexShader, PixelShader* pixelShader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();

	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->setVertexBuffer(vertexBuffer);

	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::getInstance()->getImmediateDeviceContext()->drawTriangleStrip(vertexBuffer->getSizeVertexList(), 0);
}
