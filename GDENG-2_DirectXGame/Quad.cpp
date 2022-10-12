#include "Quad.h"

#include <iostream>

void Quad::initializeObject(int num, void* shader_byte_code, size_t size_shader)
{
	AGameObject::initializeObject(num, shader_byte_code, size_shader);
	vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();

	vertex list1[] =
	{
		//Quadrilateral
		//POSITION1						COLOR1							COLOR2
		{Vector3D(-0.5f,-0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}, // POS1
		{Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}, // POS2
		{Vector3D( 0.5f,-0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}, // POS3
		{Vector3D( 0.5f, 0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}  // POS4
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

//void Quad::setAnimSpeed(float minSpeed, float maxSpeed)
//{
//	if (incAnimSpeed < minSpeed || incAnimSpeed < maxSpeed) 
//	{
//		incAnimSpeed += EngineTime::getDeltaTime();
//
//		if (incAnimSpeed >= maxSpeed)
//		{
//			decAnimSpeed = incAnimSpeed;
//			incAnimSpeed = 69;
//		}
//	}
//	else if (decAnimSpeed >= maxSpeed || decAnimSpeed > minSpeed)
//	{
//		decAnimSpeed -= EngineTime::getDeltaTime();
//
//		if (decAnimSpeed < minSpeed) 
//		{
//			incAnimSpeed = decAnimSpeed;
//			decAnimSpeed = 0;
//		}
//	}
//}

void Quad::updateObject(RECT client_rect)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	
	cc.m_world.setIdentity();

	updateObjectPosition();
	updateObjectScale();

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(client_rect.right - client_rect.left) / 200.0f,
		(client_rect.bottom - client_rect.top) / 200.0f,
		-4.0f,
		4.0f
	);

	//if (incAnimSpeed == 69)
	//	cc.m_angle += decAnimSpeed * EngineTime::getDeltaTime();
	//else if (decAnimSpeed == 0)
	//	cc.m_angle += incAnimSpeed * EngineTime::getDeltaTime();

	constant_buffer->update(graphicsEngine->getImmediateDeviceContext(), &cc);
}

void Quad::updateObjectPosition()
{
	deltaPosition += EngineTime::getDeltaTime() / 1.0f;

	matrix.setTranslation(Vector3D(0, 0, 0));
	//matrix.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), (sin(deltaPosition) + 1.0f) / 2.0f));

	cc.m_world *= matrix;
}

void Quad::updateObjectScale()
{
	deltaScale += EngineTime::getDeltaTime() / 1.0f;

	matrix.setScale(Vector3D(1.0f, 1.0f, 0));
	//matrix.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(deltaScale) + 1.0f) / 2.0f));

	cc.m_world *= matrix;
}

void Quad::drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();

	updateObject(client_rect);

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