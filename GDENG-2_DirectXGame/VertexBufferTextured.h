﻿#pragma once
#include "Prerequisites.h"
#include <d3d11.h>

class VertexBufferTextured
{
public:
	VertexBufferTextured(void* list_vertices, UINT size_vertex, UINT size_list, void* shader_byte_code, size_t size_byte_shader, 
		RenderSystem* system);
	UINT getSizeVertexList();
	~VertexBufferTextured();
private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};