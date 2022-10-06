#include "RenderSystem.h"

RenderSystem* RenderSystem::sharedInstance = NULL;

RenderSystem* RenderSystem::getInstance()
{
    return sharedInstance;
}

void RenderSystem::initialize()
{
    sharedInstance = new RenderSystem();
}

void RenderSystem::destroy()
{
    delete sharedInstance;
}

std::list<Quad*> RenderSystem::getQuadsList()
{
    return quadsList;
}

void RenderSystem::initializeQuads(int num, void* shader_byte_code, size_t size_shader)
{
    Quad* quadrilateral = new Quad();
    quadrilateral->initializeObject(num, shader_byte_code, size_shader);

    if (quadrilateral != nullptr) {
        quadsList.push_front(quadrilateral);
    } 
}

void RenderSystem::drawQuads(VertexShader* vertexShader, PixelShader* pixelShader)
{
    //Iterate through the list of quads
    for (auto const& i : RenderSystem::getInstance()->getQuadsList())
    {
        i->drawObject(vertexShader, pixelShader);
    }
}

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}
