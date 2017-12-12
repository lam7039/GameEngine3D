#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "DirectX9\Direct3D.h"

namespace se {

	class Terrain {
	public:
		Terrain();
		void Render();
		void Release();
	private:
		int m_byteCount;
		Vector3<float> m_rotation;
		Vector3<float> m_position;
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
		LPDIRECT3DTEXTURE9 m_texture;
	};

}

#endif