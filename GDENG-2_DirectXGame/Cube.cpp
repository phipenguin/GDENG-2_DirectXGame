#include "Cube.h"

void Cube::initializeObject(int num, void* shader_byte_code, size_t size_shader)
{
	AGameObject::initializeObject(num, shader_byte_code, size_shader);
	vertex_buffer = GraphicsEngine::getInstance()->createVertexBuffer();
	index_buffer = GraphicsEngine::getInstance()->createIndexBuffer();

	cubevertex vextex_list[] =
	{
		//Cuboid
		//FRONT FACE
		//POSITION						COLOR1							COLOR2
		{Vector3D(-0.5f,-0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D(-0.5f, 0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D( 0.5f, 0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D( 0.5f,-0.5f,-0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},

		//BACK FACE
		{Vector3D( 0.5f,-0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D( 0.5f, 0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D(-0.5f, 0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)},
		{Vector3D(-0.5f,-0.5f, 0.5f),	Vector3D( 0.4f, 1.0f, 0.5f),	Vector3D( 1.0f, 0.4f, 0.7f)}
	};

	UINT size_vertex_list = ARRAYSIZE(vextex_list);
	vertex_buffer->load(vextex_list, sizeof(cubevertex), size_vertex_list, shader_byte_code, size_shader);

	unsigned int index_list[]=
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	UINT size_index_list = ARRAYSIZE(index_list);
	index_buffer->load(index_list, size_index_list);

	cc.m_angle = 0;

	constant_buffer = GraphicsEngine::getInstance()->createConstantBuffer();
	constant_buffer->load(&cc, sizeof(cubeconstant));
}

void Cube::destroyObject()
{
	vertex_buffer->release();
	index_buffer->release();
	constant_buffer->release();
	AGameObject::destroyObject();
}

void Cube::drawObject(VertexShader* vertex_shader, PixelShader* pixel_shader, RECT client_rect)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();

	updateObject(client_rect);

	graphicsEngine->getImmediateDeviceContext()->setConstantBuffer(vertex_shader, constant_buffer);
	graphicsEngine->getImmediateDeviceContext()->setConstantBuffer(pixel_shader, constant_buffer);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	graphicsEngine->getImmediateDeviceContext()->setVertexShader(vertex_shader);
	graphicsEngine->getImmediateDeviceContext()->setPixelShader(pixel_shader);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	graphicsEngine->getImmediateDeviceContext()->setVertexBuffer(vertex_buffer);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	graphicsEngine->getImmediateDeviceContext()->setIndexBuffer(index_buffer);

	// FINALLY DRAW THE TRIANGLE
	graphicsEngine->getImmediateDeviceContext()->drawIndexedTriangleList(index_buffer->getSizeIndexList(), 0, 0);
}

void Cube::updateObject(RECT client_rect)
{
	GraphicsEngine* graphicsEngine = GraphicsEngine::getInstance();
	
	cc.m_world.setIdentity();

	updateObjectPosition();
	updateObjectScale();
	updateObjectRotation();

	cc.m_view.setIdentity();
	cc.m_proj.setOrthoLH
	(
		(client_rect.right - client_rect.left) / 400.0f,
		(client_rect.bottom - client_rect.top) / 400.0f,
		-4.0f,
		4.0f
	);

	cc.m_angle += 1.57f * EngineTime::getDeltaTime();

	constant_buffer->update(graphicsEngine->getImmediateDeviceContext(), &cc);
}

void Cube::updateObjectPosition()
{
	//deltaPosition += EngineTime::getDeltaTime() / 1.0f;

	matrix.setTranslation(Vector3D(0, 0, 0));
	//matrix.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f, 1.5f, 0), (sin(deltaPosition) + 1.0f) / 2.0f));

	cc.m_world *= matrix;
}

void Cube::updateObjectRotation()
{
	matrix.setIdentity();
	matrix.setRotationZ(deltaScale);
	cc.m_world *= matrix;

	matrix.setIdentity();
	matrix.setRotationY(deltaScale);
	cc.m_world *= matrix;

	matrix.setIdentity();
	matrix.setRotationX(deltaScale);
	cc.m_world *= matrix;
}

void Cube::updateObjectScale()
{
	deltaScale += EngineTime::getDeltaTime() / 1.0f;

	matrix.setScale(Vector3D(1.0f, 1.0f, 1.0f));
	//matrix.setScale(Vector3D::lerp(Vector3D(0.5f, 0.5f, 0), Vector3D(1.0f, 1.0f, 0), (sin(deltaScale) + 1.0f) / 2.0f));

	cc.m_world *= matrix;
}