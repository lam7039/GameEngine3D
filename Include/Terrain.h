#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "Object.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Terrain : public Object {
public:
	Terrain(LPDIRECT3DDEVICE9 device);
	void Render();
private:
	LPDIRECT3DDEVICE9 m_device;
	LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
	LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
};

SE_END_NAMESPACE

#endif