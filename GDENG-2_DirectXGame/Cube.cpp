#include "Cube.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "SceneCameraHandler.h"
#include <iostream>

Cube::Cube(string name, void* shader_byte_code, size_t size_shader) : AGameObject(name)
{
	Vertex vextex_list[] =
	{
		//POSITION										COLOR1										COLOR2
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D( 1.0f, 0.0f, 0.0f),	Vector3D( 1.0f, 0.0f, 0.0f)},
		{Vector3D(-0.5f, 0.5f,-0.5f),	Vector3D( 0.0f, 1.0f, 0.0f),	Vector3D( 0.0f, 1.0f, 0.0f)},
		{Vector3D( 0.5f, 0.5f,-0.5f),	Vector3D( 0.0f, 0.0f, 1.0f),	Vector3D( 0.0f, 0.0f, 1.0f)},
		{Vector3D( 0.5f,-0.5f,-0.5f),	Vector3D( 1.0f, 1.0f, 0.0f),	Vector3D( 1.0f, 1.0f, 0.0f)},

		//BACK FACE
		{Vector3D( 0.5f,-0.5f, 0.5f),	Vector3D( 0.0f, 1.0f, 1.0f),	Vector3D( 0.0f, 1.0f, 1.0f)},
		{Vector3D( 0.5f, 0.5f, 0.5f),	Vector3D( 1.0f, 0.0f, 1.0f),	Vector3D( 1.0f, 0.0f, 1.0f)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D( 0.7f, 0.1f, 0.2f),	Vector3D( 0.7f, 0.1f, 0.2f)},
		{Vector3D(-0.5f,-0.5f, 0.5f),	Vector3D( 0.3f, 0.3f, 0.3f),	Vector3D( 0.3f, 0.3f, 0.3f)}

		//POSITION						COLOR1							COLOR2
		//FRONT FACE
		//{Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		//{Vector3D(-0.5f, 0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		//{Vector3D( 0.5f, 0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		//{Vector3D( 0.5f,-0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},

		////BACK FACE
		//{Vector3D( 0.5f,-0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		//{Vector3D( 0.5f, 0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		//{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		//{Vector3D(-0.5f,-0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}
	};

	vertex_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBuffer(vextex_list, 
		sizeof(Vertex), ARRAYSIZE(vextex_list), shader_byte_code, size_shader);

	unsigned int index_list[]=
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	index_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	CBData cbData = {};
	cbData.time = 0;

	constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cbData, sizeof(CBData));
}

Cube::~Cube()
{
	AGameObject::~AGameObject();
}

void Cube::update(float deltaTime)
{
	this->deltaTime = deltaTime;

	this->ticks += deltaTime;
	
	//float rotSpeed = this->ticks * this->speed;
	//this->setRotation(rotSpeed, rotSpeed, rotSpeed);
	//if (isPosGoingPositive)
	//{
	//	this->setPosition(this->getLocalPosition().lerp(this->getLocalPosition(), Vector3D(1.0f, 1.0f, 0.0f), this->deltaTime * this->speed));

	//	if (this->getLocalPosition().m_x >= 0.99f && this->getLocalPosition().m_y >= 0.99f)
	//	{
	//		this->setPosition(1.0f, 1.0f, 0.0f);
	//		isPosGoingPositive = false;
	//	}

	//	if (!isScaleGettingBigger)
	//	{
	//		this->setScale(this->getLocalScale().lerp(this->getLocalScale(), Vector3D(0.25f, 0.25f, 0.25f), this->deltaTime * this->speed));

	//		if (this->getLocalScale().m_x <= 0.26f && this->getLocalScale().m_y <= 0.26f && this->getLocalScale().m_z <= 0.26f)
	//		{
	//			this->setScale(0.25f, 0.25f, 0.25f);
	//			isScaleGettingBigger = true;
	//		}
	//	}
	//}
	//else
	//{
	//	this->setPosition(this->getLocalPosition().lerp(this->getLocalPosition(), Vector3D(-1.0f, -1.0f, 0.0f), this->deltaTime * this->speed));

	//	if (this->getLocalPosition().m_x <= -0.99f && this->getLocalPosition().m_y <= -0.99f)
	//	{
	//		this->setPosition(-1.0f, -1.0f, 0.0f);
	//		isPosGoingPositive = true;
	//	}

	//	if (isScaleGettingBigger)
	//	{
	//		this->setScale(this->getLocalScale().lerp(this->getLocalScale(), Vector3D(1.0f, 1.0f, 1.0f), this->deltaTime * this->speed));

	//		if (this->getLocalScale().m_x >= 0.99f && this->getLocalScale().m_y >= 0.99f && this->getLocalScale().m_z >= 0.99f)
	//		{
	//			this->setScale(1.0f, 1.0f, 1.0f);
	//			isScaleGettingBigger = false;
	//		}
	//	}
	//}

	//if (isCubeWarpingToPlane)
	//{
	//	this->setScale(this->getLocalScale().lerp(this->getLocalScale(), Vector3D(1.0f, 0.005f, 1.0f), this->deltaTime * this->speed));

	//	if (this->getLocalScale().m_x >= 0.99f && this->getLocalScale().m_y <= 0.0059f && this->getLocalScale().m_z >= 0.99f)
	//	{
	//		this->setScale(1.0f, 0.005f, 1.0f);
	//		isCubeWarpingToPlane = false;
	//	}
	//}
	//else
	//{
	//	this->setScale(this->getLocalScale().lerp(this->getLocalScale(), Vector3D(0.5f, 0.5f, 0.5f), this->deltaTime * this->speed));

	//	if (this->getLocalScale().m_x >= 0.49f && this->getLocalScale().m_y >= 0.49f && this->getLocalScale().m_z >= 0.49f)
	//	{
	//		this->setScale(0.5f, 0.5f, 0.5f);
	//		isCubeWarpingToPlane = true;
	//	}
	//}
}

void Cube::draw(int width, int height, VertexShaderPtr vertex_shader, PixelShaderPtr pixel_shader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContextPtr deviceContext = graphicsEngine->getInstance()->getRenderSystem()->getImmediateDeviceContext();

	CBData cbData = {};
	cbData.time = this->ticks;

	if (this->deltaPosition > 1.0f)
	{
		this->deltaPosition = 0.0f;
	}
	else
	{
		this->deltaPosition += this->deltaTime * 0.1f;
	}

	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);

	//Scale -> Rotate -> Transform
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix *= xMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= zMatrix;

	allMatrix *= scaleMatrix;
	allMatrix *= rotMatrix;
	allMatrix *= translationMatrix;

	cbData.worldMatrix = allMatrix;

	Matrix4x4 cameraMatrix = SceneCameraHandler::getInstance()->getSceneCameraViewMatrix();
	cbData.viewMatrix = cameraMatrix;

	float aspectRatio = (float)width / (float)height;
	cbData.projMatrix.setPerspectiveFovLH(aspectRatio, aspectRatio, 0.1f, 1000.0f);

	//std::cout << "Rotation: " << "(" << this->getLocalRotation().m_x << ", " << this->getLocalRotation().m_y << ", " << this->getLocalRotation().m_z << ")" << std::endl;

	//cbData.viewMatrix.setIdentity();
	//cbData.projMatrix.setOrthoLH(width / 400.0f, height / 400.0f, -4.0f, 4.0f);

	constant_buffer->update(deviceContext, &cbData);

	deviceContext->setConstantBuffer(vertex_shader, this->constant_buffer);
	deviceContext->setConstantBuffer(pixel_shader, this->constant_buffer);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	deviceContext->setVertexShader(vertex_shader);
	deviceContext->setPixelShader(pixel_shader);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	deviceContext->setVertexBuffer(vertex_buffer);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	deviceContext->setIndexBuffer(index_buffer);

	// FINALLY DRAW THE TRIANGLE
	deviceContext->drawIndexedTriangleList(index_buffer->getSizeIndexList(), 0, 0);
}

void Cube::setAnimationSpeed(float speed)
{
	this->speed = speed;
}