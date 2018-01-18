#ifndef DIRECTXMESH_H
#define DIRECTXMESH_H

#include "Asset.h"
#include "DirectX9\Direct3D.h"
#include "Debug.h"

namespace se {

	///
	/// The mesh for DirectX 9
	///
	class Mesh : public AbstractAsset {
	public:
		Mesh(LPDIRECT3DDEVICE9 device, const std::string &path);
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
		LPDIRECT3DDEVICE9 m_device;
	};

}

#endif