#pragma once
#include "Plane.h"
#include "Cube.h"
#include <list>

class RenderSystem
{
public:
	static void initialize();
	static void destroy();
	static RenderSystem* getInstance();
	
	//For Planes
	void initializePlanes(void* shader_byte_code, size_t size_shader);
	void drawPlanes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader);

	//For Cubes
	void initializeCubes(void* shader_byte_code, size_t size_shader);
	void drawCubes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader);

private:
	RenderSystem();
	~RenderSystem();
	RenderSystem(RenderSystem const&) {};
	RenderSystem& operator=(RenderSystem const&) {};

	static RenderSystem* sharedInstance;

	std::list<Plane*> planesList;
	std::list<Cube*> cubesList;
};