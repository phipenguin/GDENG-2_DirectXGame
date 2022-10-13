#pragma once
//#include "Quad.h"
#include "Cube.h"
#include <list>

class RenderSystem
{
public:
	static void initialize();
	static void destroy();
	static RenderSystem* getInstance();
	
	//For Quads
	//void initializeQuads(int num, void* shader_byte_code, size_t size_shader);
	//void drawQuads(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect);

	//For Cubes
	void initializeCubes(void* shader_byte_code, size_t size_shader);
	void drawCubes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader);

private:
	RenderSystem();
	~RenderSystem();
	RenderSystem(RenderSystem const&) {};
	RenderSystem& operator=(RenderSystem const&) {};

	static RenderSystem* sharedInstance;

	//std::list<Quad*> quadsList;
	std::list<Cube*> cubesList;
};