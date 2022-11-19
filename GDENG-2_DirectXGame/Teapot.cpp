#include "Teapot.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "DeviceContext.h"
#include "Mesh.h"
#include "SceneCameraHandler.h"

Teapot::Teapot(string name) : AGameObject(name)
{
	CBData cbData = {};
	cbData.time = 0;

	this->constant_buffer = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cbData, sizeof(CBData));
}

Teapot::~Teapot()
{
	AGameObject::~AGameObject();
}

void Teapot::update(float deltaTime)
{
	this->deltaTime = deltaTime;

	this->ticks += deltaTime;
}

void Teapot::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContextPtr deviceContext = graphicsEngine->getInstance()->getRenderSystem()->getImmediateDeviceContext();
	mesh = GraphicsEngine::getInstance()->getMeshManager()->createMeshFromFile(L"Assets\\Meshes\\teapot.obj");

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.VERTEX_MESH_LAYOUT_SHADER_NAME), 
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	CBData cbData = {};
	cbData.time = this->ticks;

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

	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shaderNames.VERTEX_MESH_LAYOUT_SHADER_NAME), this->constant_buffer);
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME), this->constant_buffer);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	deviceContext->setVertexBufferTextured(mesh->getVertexBufferTextured());
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	deviceContext->setIndexBuffer(mesh->getIndexBuffer());

	// FINALLY DRAW THE TRIANGLE
	deviceContext->drawIndexedTriangleList(mesh->getIndexBuffer()->getSizeIndexList(), 0, 0);
}

void Teapot::setAnimationSpeed(float speed)
{
	this->speed = speed;
}