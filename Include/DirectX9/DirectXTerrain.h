#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "Asset.h"
#include "Bitmap.h"
#include "DirectX9\Direct3D.h"

namespace se {

	class Terrain : public AbstractAsset {
	public:
		void Create();
		void Load();
		void Process();
		void Release();
	private:
		Bitmap m_bitmap;
		unsigned long m_width;
		unsigned long m_height;
		Transform3f m_transform;
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		//LPDIRECT3DINDEXBUFFER9 m_indexBuffer;
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
		LPDIRECT3DTEXTURE9 m_texture;
	};

}

#endif