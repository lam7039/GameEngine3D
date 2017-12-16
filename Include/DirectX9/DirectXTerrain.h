#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "Asset.h"
#include "DirectX9\Direct3D.h"

namespace se {

	class Terrain : public AbstractAsset {
	public:
		void Create();
		void Load();
		void Process();
		void Release();
	private:
		int m_width;
		int m_height;
		Vector3<float> m_rotation;
		Vector3<float> m_position;
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		//LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
		//TODO: use LPDIRECT3DTEXTURE9 for texture like in mesh maybe?
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
		LPDIRECT3DTEXTURE9 m_texture;
	};

}

#endif