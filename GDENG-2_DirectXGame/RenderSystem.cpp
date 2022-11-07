#include "RenderSystem.h"
#include "EngineTime.h"
#include "AppWindow.h"
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

void RenderSystem::initializePlanes(void* shader_byte_code, size_t size_shader)
{
    AppWindow* appWindow = AppWindow::getInstance();

	Plane* plane = new Plane("Plane", shader_byte_code, size_shader);
    plane->setAnimationSpeed(2.0f);

 //   //Level 1
 //   if (appWindow->numOfCards == 1 || appWindow->numOfCards == 3 || appWindow->numOfCards == 5)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, 1.0f);

 //       if (appWindow->numOfCards == 1)
 //       	plane->setPosition(Vector3D(-1.6f, 0.0f, 0.0f));
	//	else if (appWindow->numOfCards == 3)
 //   		plane->setPosition(Vector3D(1.6f, 0.0f, 0.0f));
 //       else if (appWindow->numOfCards == 5)
 //   		plane->setPosition(Vector3D(4.8f, 0.0f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
	//if (appWindow->numOfCards == 2 || appWindow->numOfCards == 4 || appWindow->numOfCards == 6)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	if (appWindow->numOfCards == 2)
 //       	plane->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	//	else if (appWindow->numOfCards == 4)
 //   		plane->setPosition(Vector3D(3.2f, 0.0f, 0.0f));
 //       else if (appWindow->numOfCards == 6)
 //   		plane->setPosition(Vector3D(6.4f, 0.0f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
 //   if (appWindow->numOfCards == 7 || appWindow->numOfCards == 8)
 //   {
 //       //plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	if (appWindow->numOfCards == 7)
 //       	plane->setPosition(Vector3D(0.3f, 1.3f, 0.0f));
	//	else if (appWindow->numOfCards == 8)
 //   		plane->setPosition(Vector3D(4.3f, 1.3f, 0.0f));

 //       plane->setScale(Vector3D(2.0f, 0.0f, 0.5f));
 //   }
 //   //Level 2
 //   if (appWindow->numOfCards == 9 || appWindow->numOfCards == 10)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, 1.0f);

 //       if (appWindow->numOfCards == 9)
 //       	plane->setPosition(Vector3D(0.0f, 2.6f, 0.0f));
	//	else if (appWindow->numOfCards == 10)
 //   		plane->setPosition(Vector3D(3.2f, 2.6f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
 //   if (appWindow->numOfCards == 11 || appWindow->numOfCards == 12)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //       if (appWindow->numOfCards == 11)
 //       	plane->setPosition(Vector3D(1.6f, 2.6f, 0.0f));
	//	else if (appWindow->numOfCards == 12)
 //   		plane->setPosition(Vector3D(4.8f, 2.6f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
 //   if (appWindow->numOfCards == 13)
 //   {
 //       //plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	plane->setPosition(Vector3D(2.3f, 3.9f, 0.0f));

 //       plane->setScale(Vector3D(2.0f, 0.0f, 0.5f));
 //   }
 //   //Level 3
 //   if (appWindow->numOfCards == 14)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, 1.0f);

 //   	plane->setPosition(Vector3D(1.6f, 5.1f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
	//if (appWindow->numOfCards == 15)
 //   {
 //       plane->setRotation(plane->getLocalRotation().m_x, plane->getLocalRotation().m_y, -1.0f);

 //   	plane->setPosition(Vector3D(3.2f, 5.1f, 0.0f));

 //       plane->setScale(Vector3D(1.5f, 0.0f, 0.5f));
 //   }
    plane->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
    plane->setScale(Vector3D(1.0f, 1.0f, 1.0f));
    this->planesList.push_front(plane);
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
	//std::random_device rd; // obtain a random number from hardware
	//std::mt19937 gen(rd()); // seed the generator
	//std::uniform_int_distribution<> distr(0, 15); // define the range

    AppWindow* appWindow = AppWindow::getInstance();

    Cube* cuboid = new Cube("Cube", shader_byte_code, size_shader);
    cuboid->setAnimationSpeed(2.0f);

 //   if (appWindow->numOfCubes == 1)
 //   	cuboid->setPosition(Vector3D(0.0f, 0.9f, 0.0f));
 //   else if (appWindow->numOfCubes == 2)
 //       cuboid->setPosition(Vector3D(-1.5f, 2.0f, 0.0f));
	//else if (appWindow->numOfCubes == 3)
 //   	cuboid->setPosition(Vector3D(-1.5f, 3.0f, -2.0f));

	cuboid->setPosition(Vector3D(0.0f, 0.0f, 0.0f));
	cuboid->setScale(Vector3D(1.0f, 1.0f, 1.0f));
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