#ifndef DIRECTXMESH_H
#define DIRECTXMESH_H

#include "Asset.h"
#include "DirectX9\Direct3D.h"
#include "Debug.h"

namespace se {

	class Mesh : public AbstractAsset {
	public:
		Mesh(const std::string &path);
		void Create() override;
		void Load() override;
		void Process() override;
		void Release() override;
	private:
		Debug m_logger;
		LPD3DXMESH m_mesh;
		LPDIRECT3DTEXTURE9 *m_meshTextures;
		D3DMATERIAL9 *m_meshMaterials;
		DWORD m_materialCount;
	};

}

#endif