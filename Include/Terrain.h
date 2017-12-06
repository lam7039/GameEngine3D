#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "Entity.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

//TODO: Terrain shouldn't be an object, but just be in a scene. This is a temporary solution to easily switch between scenes for the expert meeting
class Terrain : public Entity {
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