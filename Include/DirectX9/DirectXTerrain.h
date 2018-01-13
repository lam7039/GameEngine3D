#ifndef TERRAIN_H
#define TERRAIN_H

#include "std.h"
#include "Asset.h"
#include "Bitmap.h"
#include "DirectX9\Direct3D.h"
#include "Debug.h"

namespace se {

	class Terrain : public AbstractAsset {
	public:
		Terrain(const std::string &heightMap, const std::string &texture);
		void Create() override;
		void Load() override;
		void Process() override;
		void Release() override;
	private:
		Debug m_logger;
		Bitmap m_bitmap;
		unsigned long m_width;
		unsigned long m_height;
		Transform3f m_transform;
		LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
		D3DXMATRIX m_matRotate;
		D3DXMATRIX m_matTranslate;
		LPDIRECT3DTEXTURE9 m_texture;
		std::string m_pathHeightMap;
		std::string m_pathTexture;
	};

}

#endif