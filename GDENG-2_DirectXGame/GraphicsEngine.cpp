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
	delete sharedInstance->getRenderSystem();
	delete sharedInstance->getTextureManager();
	delete sharedInstance;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}