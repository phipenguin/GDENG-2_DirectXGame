#pragma once
#include "Cube.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

class TexturedCube : public Cube
{
public:
	TexturedCube(string name);
	~TexturedCube();

	void draw(int width, int height) override;

private:
	TexturePtr woodTex;

	VertexBufferTexturedPtr m_vertex_buffer_textured;

	struct Vertex
	{
		Vector3D position;
		Vector2D texcoord;
	};
};