#include "GraphicsEngine.h"

GraphicsEngine* GraphicsEngine::sharedInstance = NULL;

GraphicsEngine* GraphicsEngine::getInstance()
{
	return sharedInstance;
}

void GraphicsEngine::initialize()
{
	sharedInstance = new GraphicsEngine();

	sharedInstance->m_render_system = new RenderSystem();
	sharedInstance->m_tex_manager = new TextureManager();
}

void GraphicsEngine::destroy()
{
	delete sharedInstance->getTextureManager();
	delete sharedInstance->getMeshManager();
	delete sharedInstance->getRenderSystem();
	delete sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return this->m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return this->m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return this->m_mesh_manager;
}

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::initializeMeshManager()
{
	sharedInstance->m_mesh_manager = new MeshManager();
}