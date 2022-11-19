#pragma once
#include "Resource.h"
#include "VertexBufferTextured.h"
#include "IndexBuffer.h"

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* full_path);
	~Mesh();

	const VertexBufferTexturedPtr& getVertexBufferTextured();
	const IndexBufferPtr& getIndexBuffer();

private:
	VertexBufferTexturedPtr m_vertex_buffer_textured;
	IndexBufferPtr m_index_buffer;

	friend class DeviceContext;
};