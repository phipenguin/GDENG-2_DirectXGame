#include "ShaderLibrary.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

ShaderLibrary* ShaderLibrary::sharedInstance = nullptr;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(String vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	graphicsEngine->getRenderSystem()->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
}

VertexShaderPtr ShaderLibrary::getVertexShader(String vertexShaderName)
{
	if (this->activeVertexShaders[vertexShaderName] == NULL)
	{
		std::cout << "Vertex Shader " << vertexShaderName.c_str() << " not found." << std::endl;
	}
	return this->activeVertexShaders[vertexShaderName];
}

PixelShaderPtr ShaderLibrary::getPixelShader(String pixelShaderName)
{
	if (this->activeVertexShaders[pixelShaderName] == NULL)
	{
		std::cout << "Pixel Shader " << pixelShaderName.c_str() << " not found." << std::endl;
	}
	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();

	ShaderNames shaderNames;
	ShaderData shaderData;
	graphicsEngine->getRenderSystem()->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = graphicsEngine->getRenderSystem()->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	graphicsEngine->getRenderSystem()->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = graphicsEngine->getRenderSystem()->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	graphicsEngine->getRenderSystem()->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = graphicsEngine->getRenderSystem()->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	graphicsEngine->getRenderSystem()->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = graphicsEngine->getRenderSystem()->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	std::cout << "Shader Library initialized." << std::endl;
}

ShaderLibrary::~ShaderLibrary()
{
	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}