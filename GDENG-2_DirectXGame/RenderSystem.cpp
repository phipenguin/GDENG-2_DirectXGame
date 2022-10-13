#include "RenderSystem.h"
#include "EngineTime.h"
#include <random>

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

//void RenderSystem::initializeQuads(int num, void* shader_byte_code, size_t size_shader)
//{
//	Quad* quadrilateral = new Quad();
//    quadrilateral->initializeObject(num, shader_byte_code, size_shader);
//
//    if (quadrilateral != NULL) {
//        quadsList.push_front(quadrilateral);
//    } 
//}
//
//void RenderSystem::drawQuads(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect)
//{
//    //Iterate through the list of quads
//    for (auto const& i : quadsList)
//    {
//        //i->setAnimSpeed(1.57f, 10.0f);
//        i->drawObject(vertex_shader, pixel_shader, client_rect);
//    }
//}

void RenderSystem::initializeCubes(void* shader_byte_code, size_t size_shader)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(-0.75f, 0.75f);
    std::uniform_real_distribution<> distr1(-3.75f, 3.75f);
    //std::uniform_real_distribution<> distr1(10.0f, 10.0f);

    for (int i = 0; i < 100; i++)
    {
        float x = distr(gen);
        float y = distr(gen);

	    Cube* cuboid = new Cube("Cube", shader_byte_code, size_shader);
        cuboid->setAnimationSpeed(distr1(gen));
        cuboid->setPosition(Vector3D(x, y, 0));
        cuboid->setScale(Vector3D(0.25, 0.25, 0.25));
        this->cubesList.push_front(cuboid);
    }
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