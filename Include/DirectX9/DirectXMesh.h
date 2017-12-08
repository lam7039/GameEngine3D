#ifndef DIRECTXMESH_H
#define DIRECTXMESH_H

#include "Asset.h"
#include "DirectX9/Direct3D.h"

namespace se {

	class Mesh : public AbstractAsset {
	public:
		Mesh(const std::string &path);
		void Create();
		void Load();
		void Render();
		void Release();
	private:
		LPD3DXMESH m_mesh;
		LPDIRECT3DTEXTURE9 *m_meshTextures;
		D3DMATERIAL9 *m_meshMaterials;
		DWORD m_materialCount;
	};

}

#endif