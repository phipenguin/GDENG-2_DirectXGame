#include "RenderSystem.h"

RenderSystem* RenderSystem::sharedInstance = NULL;

void RenderSystem::initialize()
{
	sharedInstance = new RenderSystem();
}

void RenderSystem::destroy()
{
	delete sharedInstance;
}

RenderSystem* RenderSystem::getInstance()
{
    return sharedInstance;
}

void RenderSystem::initializeQuads(int num, void* shader_byte_code, size_t size_shader)
{
	Quad* quadrilateral = new Quad();
    quadrilateral->initializeObject(num, shader_byte_code, size_shader);

    if (quadrilateral != NULL) {
        quadsList.push_front(quadrilateral);
    } 
}

void RenderSystem::drawQuads(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect)
{
    //Iterate through the list of quads
    for (auto const& i : quadsList)
    {
        //i->setAnimSpeed(1.57f, 10.0f);
        i->drawObject(vertex_shader, pixel_shader, client_rect);
    }
}

void RenderSystem::initializeCubes(int num, void* shader_byte_code, size_t size_shader)
{
	Cube* cuboid = new Cube();
    cuboid->initializeObject(num, shader_byte_code, size_shader);

    if (cuboid != NULL) {
        cubesList.push_front(cuboid);
    } 
}

void RenderSystem::drawCubes(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect)
{
    //Iterate through the list of cubes
    for (auto const& i : cubesList)
    {
        i->drawObject(vertex_shader, pixel_shader, client_rect);
    }
}

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}
