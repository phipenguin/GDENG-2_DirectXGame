#include "Quad.h"

#include <iostream>

void Quad::initializeObject(int num, void* shader_byte_code, size_t size_shader)
{
	AGameObject::initializeObject(num, shader_byte_code, size_shader);
	vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();

	vertex list1[] =
	{
		//X - Y - Z
		//Quadrilateral
		{-0.3f,-0.1f,0.0f,		-0.7f,-0.9f, 0.0f,		0.4f,1.0f,0.5f,		1.0f,0.4f,0.7f }, // POS1
		{-0.1f, 0.8f,0.0f,		-0.9f, 0.1f, 0.0f,		0.4f,1.0f,0.5f,		1.0f,0.4f,0.7f }, // POS2
		{ 0.1f,-0.6f,0.0f,		 1.0f,-0.2f, 0.0f,		0.4f,1.0f,0.5f,		1.0f,0.4f,0.7f }, // POS3
		{ 0.8f, 0.8f,0.0f,		-0.7f,-0.9f, 0.0f,		0.4f,1.0f,0.5f,		1.0f,0.4f,0.7f }  // POS4
	};

	/*vertex list2[] =
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
	};*/

	UINT size_list = ARRAYSIZE(list1);

	//if (num == 1)
	vertex_buffer->load(list1, sizeof(vertex), size_list, shader_byte_code, size_shader);
	//else if (num == 2)
	//	vertex_buffer->load(list2, sizeof(vertex), size_list, shader_byte_code, size_shader);
	//else if (num == 3)
	//	vertex_buffer->load(list3, sizeof(vertex), size_list, shader_byte_code, size_shader);
	
	cc.m_angle = 0;

	constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constant_buffer->load(&cc, sizeof(constant));
}

void Quad::destroyObject()
{
	AGameObject::destroyObject();
}

void Quad::setAnimSpeed(float minSpeed, float maxSpeed)
{
	if (incAnimSpeed < minSpeed || incAnimSpeed < maxSpeed) 
	{
		incAnimSpeed += EngineTime::getDeltaTime();

		if (incAnimSpeed >= maxSpeed)
		{
			decAnimSpeed = incAnimSpeed;
			incAnimSpeed = 69;
		}
	}
	else if (decAnimSpeed >= maxSpeed || decAnimSpeed > minSpeed)
	{
		decAnimSpeed -= EngineTime::getDeltaTime();

		if (decAnimSpeed < minSpeed) 
		{
			incAnimSpeed = decAnimSpeed;
			decAnimSpeed = 0;
		}
	}
}

void Quad::drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();

	if (incAnimSpeed == 69)
		cc.m_angle += decAnimSpeed * EngineTime::getDeltaTime();
	else if (decAnimSpeed == 0)
		cc.m_angle += incAnimSpeed * EngineTime::getDeltaTime();

	std::cout << "Animation Speed: " << cc.m_angle << std::endl;

	constant_buffer->update(graphicsEngine->getImmediateDeviceContext(), &cc);

	graphicsEngine->getImmediateDeviceContext()->setConstantBuffer(vertex_shader, constant_buffer);
	graphicsEngine->getImmediateDeviceContext()->setConstantBuffer(pixel_shader, constant_buffer);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	graphicsEngine->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	graphicsEngine->getImmediateDeviceContext()->setPixelShader(pixel_shader);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	graphicsEngine->getImmediateDeviceContext()->setVertexBuffer(vertex_buffer);

	// FINALLY DRAW THE TRIANGLE
	graphicsEngine->getImmediateDeviceContext()->drawTriangleStrip(vertex_buffer->getSizeVertexList(), 0);
}