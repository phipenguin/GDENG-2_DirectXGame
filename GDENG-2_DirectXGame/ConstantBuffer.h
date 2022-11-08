#pragma once
#include "Prerequisites.h"
#include <d3d11.h>

class ConstantBuffer
{
public:
	ConstantBuffer(void* buffer, UINT size_buffer, RenderSystem* system);
	void update(DeviceContext* context, void* buffer);
	~ConstantBuffer();
private:
	ID3D11Buffer* m_buffer;
	RenderSystem* m_system = nullptr;
private:
	friend class DeviceContext;
};