#include "TexturedCube.h"
#include "GraphicsEngine.h"
#include "ShaderLibrary.h"
#include "DeviceContext.h"
#include "TextureManager.h"
#include "SceneCameraHandler.h"

TexturedCube::TexturedCube(string name) : Cube(name)
{
	ShaderNames shaderNames;
	void* shaderByteCode = NULL;
	size_t sizeShader = 0;
	ShaderLibrary::getInstance()->requestVertexShaderData(shaderNames.TEXTURED_VERTEX_SHADER_NAME, &shaderByteCode, &sizeShader);

	Vector3D position_list[] =
	{
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f)},
		{Vector3D(-0.5f, 0.5f,-0.5f)},
		{Vector3D( 0.5f, 0.5f,-0.5f)},
		{Vector3D( 0.5f,-0.5f,-0.5f)},

		//BACK FACE
		{Vector3D( 0.5f,-0.5f, 0.5f)},
		{Vector3D( 0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f, 0.5f, 0.5f)},
		{Vector3D(-0.5f,-0.5f, 0.5f)}
	};

	Vector2D texcoord_list[] =
	{
		{Vector2D(0.0f, 0.0f)},
		{Vector2D(0.0f, 1.0f)},
		{Vector2D(1.0f, 0.0f)},
		{Vector2D(1.0f, 1.0f)}
	};

	Vertex vextex_list[] =
	{
		{ position_list[0],texcoord_list[1] },
		{ position_list[1],texcoord_list[0] },
		{ position_list[2],texcoord_list[2] },
		{ position_list[3],texcoord_list[3] },


		{ position_list[4],texcoord_list[1] },
		{ position_list[5],texcoord_list[0] },
		{ position_list[6],texcoord_list[2] },
		{ position_list[7],texcoord_list[3] },


		{ position_list[1],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[2],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[0],texcoord_list[0] },
		{ position_list[3],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[3],texcoord_list[1] },
		{ position_list[2],texcoord_list[0] },
		{ position_list[5],texcoord_list[2] },
		{ position_list[4],texcoord_list[3] },

		{ position_list[7],texcoord_list[1] },
		{ position_list[6],texcoord_list[0] },
		{ position_list[1],texcoord_list[2] },
		{ position_list[0],texcoord_list[3] }
	};

	m_vertex_buffer_textured = GraphicsEngine::getInstance()->getRenderSystem()->createVertexBufferTextured(vextex_list, 
		sizeof(Vertex), ARRAYSIZE(vextex_list), shaderByteCode, sizeShader);

	unsigned int index_list[]=
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		8,9,10,
		10,11,8,
		//BOTTOM SIDE
		12,13,14,
		14,15,12,
		//RIGHT SIDE
		16,17,18,
		18,19,16,
		//LEFT SIDE
		20,21,22,
		22,23,20
	};

	this->getIndexBuffer() = GraphicsEngine::getInstance()->getRenderSystem()->createIndexBuffer(index_list, ARRAYSIZE(index_list));

	CBData cbData = {};
	cbData.time = 0;

	this->getConstantBuffer() = GraphicsEngine::getInstance()->getRenderSystem()->createConstantBuffer(&cbData, sizeof(CBData));
}

TexturedCube::~TexturedCube()
{
	AGameObject::~AGameObject();
}

void TexturedCube::draw(int width, int height)
{
	ShaderNames shaderNames;
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	DeviceContextPtr deviceContext = graphicsEngine->getInstance()->getRenderSystem()->getImmediateDeviceContext();
	woodTex = GraphicsEngine::getInstance()->getTextureManager()->createTextureFromFile(L"Assets\\Textures\\wood.jpg");

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	deviceContext->setRenderConfig(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME), 
		ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME));

	CBData cbData = {};
	cbData.time = this->getTicks();

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

	this->getConstantBuffer()->update(deviceContext, &cbData);

	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME), this->getConstantBuffer());
	deviceContext->setConstantBuffer(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME), this->getConstantBuffer());

	deviceContext->setTexture(ShaderLibrary::getInstance()->getPixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME), woodTex);

	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	deviceContext->setVertexBufferTextured(m_vertex_buffer_textured);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	deviceContext->setIndexBuffer(this->getIndexBuffer());

	// FINALLY DRAW THE TRIANGLE
	deviceContext->drawIndexedTriangleList(this->getIndexBuffer()->getSizeIndexList(), 0, 0);
}