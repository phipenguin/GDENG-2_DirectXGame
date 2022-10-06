#pragma once
#include "Quad.h"

#include <list>

class RenderSystem
{
public:
	static RenderSystem* getInstance();
	static void initialize();
	static void destroy();

	std::list<Quad*> getQuadsList();
	void initializeQuads(int num, void* shader_byte_code, size_t size_shader);
	void drawQuads(VertexShader* vertexShader, PixelShader* pixelShader);

private:
	RenderSystem();
	~RenderSystem();
	RenderSystem(RenderSystem const&) {};
	RenderSystem& operator=(RenderSystem const&) {};
	static RenderSystem* sharedInstance;

	std::list<Quad*> quadsList;
};