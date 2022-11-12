#pragma once
#include "Prerequisites.h"
#include "RenderSystem.h"

class GraphicsEngine
{
public:
	static GraphicsEngine* getInstance();
	static void initialize();
	static void destroy();

	RenderSystem* getRenderSystem();

private:
	GraphicsEngine();
	~GraphicsEngine();
	GraphicsEngine(GraphicsEngine const&) {};
	GraphicsEngine& operator=(GraphicsEngine const&) {};
	static GraphicsEngine* sharedInstance;

	RenderSystem* m_render_system = nullptr;
};