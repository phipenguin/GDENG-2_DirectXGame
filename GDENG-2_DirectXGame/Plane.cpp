#include "Plane.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"

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

Plane::Plane(string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	Vertex vextex_list[] =
	{
		//POSITION						COLOR1							COLOR2
		{Vector3D(-0.5f,-0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D(-0.5f, 0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D( 0.5f,-0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D( 0.5f, 0.5f, 0.0f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}
	};

	vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();
	vertex_buffer->load(vextex_list, sizeof(Vertex), ARRAYSIZE(vextex_list), shader_byte_code, size_shader);

	CBData cbData = {};
	cbData.time = 0;

	constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constant_buffer->load(&cbData, sizeof(CBData));
}

Plane::~Plane()
{
	vertex_buffer->release();
	constant_buffer->release();
	AGameObject::~AGameObject();
}

void Plane::update(float deltaTime)
{
	this->deltaTime = deltaTime;

	this->ticks += deltaTime;
}

void Plane::draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContext* deviceContext = graphicsEngine->getImmediateDeviceContext();
	
	CBData cbData = {};

	if (this->deltaPosition > 1.0f)
	{
		this->deltaPosition = 0.0f;
	}
	else
	{
		this->deltaPosition += this->deltaTime * 0.1f;
	}

	cbData.worldMatrix.setIdentity();
	cbData.viewMatrix.setIdentity();
	cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	//cc.m_angle += 1.57f * EngineTime::getDeltaTime();
	//if (incAnimSpeed == 69)
	//	cc.m_angle += decAnimSpeed * EngineTime::getDeltaTime();
	//else if (decAnimSpeed == 0)
	//	cc.m_angle += incAnimSpeed * EngineTime::getDeltaTime();

	constant_buffer->update(graphicsEngine->getImmediateDeviceContext(), &cbData);

	deviceContext->setConstantBuffer(vertex_shader, constant_buffer);
	deviceContext->setConstantBuffer(pixel_shader, constant_buffer);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	deviceContext->setVertexShader(vertex_shader);
	deviceContext->setPixelShader(pixel_shader);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	deviceContext->setVertexBuffer(vertex_buffer);

	// FINALLY DRAW THE TRIANGLE
	deviceContext->drawTriangleStrip(vertex_buffer->getSizeVertexList(), 0);
}

void Plane::setAnimationSpeed(float speed)
{
}