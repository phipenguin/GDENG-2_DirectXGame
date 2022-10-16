#include "RenderSystem.h"
#include "EngineTime.h"

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

void RenderSystem::initializePlanes(void* shader_byte_code, size_t size_shader)
{
	Plane* plane = new Plane("Plane", shader_byte_code, size_shader);
    plane->setAnimationSpeed(2.0f);
    plane->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
    plane->setScale(Vector3D(0.75f, 0.75f, 0.75f));

    planesList.push_front(plane);
}

void RenderSystem::drawPlanes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
    //Iterate through the list of quads
    for (auto const& i : planesList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height, vertex_shader, pixel_shader);
    }
}

void RenderSystem::initializeCubes(void* shader_byte_code, size_t size_shader)
{
    Cube* cuboid = new Cube("Cube", shader_byte_code, size_shader);
    cuboid->setAnimationSpeed(2.0f);
    cuboid->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
    cuboid->setScale(Vector3D(0.25f, 0.25f, 0.25f));
    this->cubesList.push_front(cuboid);
}

void RenderSystem::drawCubes(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
    //Iterate through the list of cubes
    for (auto const& i : cubesList)
    {
        i->update(EngineTime::getDeltaTime());
        i->draw(width, height, vertex_shader, pixel_shader);
    }
}

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}