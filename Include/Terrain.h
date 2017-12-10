#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "Entity.h"
#include "DirectX9\Direct3D.h"

namespace se {

	//TODO: Terrain shouldn't be an object, but just be in a scene. This is a temporary solution to easily switch between scenes for the expert meeting
	class Terrain : public Entity {
	public:
		Terrain();
		void Render();
	private:
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
	};

}

#endif