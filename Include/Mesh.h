#ifndef MESH_H
#define MESH_H

#include "std.h"
#include <d3dx9.h>

namespace se {

	class Mesh {
	public:
		Mesh();
		void Load(LPDIRECT3DDEVICE9 device, const std::string &path);
		void Render();
		void Release();
	private:
		LPD3DXMESH m_mesh;
		LPDIRECT3DDEVICE9 m_device;
		LPDIRECT3DTEXTURE9 *m_meshTextures;
		D3DMATERIAL9 *m_meshMaterials;
		DWORD m_materialCount;
	};

}

#endif