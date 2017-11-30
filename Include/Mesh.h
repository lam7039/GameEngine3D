#ifndef MESH_H
#define MESH_H

#include "std.h"
#include <d3dx9.h>

SE_BEGIN_NAMESPACE

class Mesh {
public:
	Mesh();
	void Load(LPDIRECT3DDEVICE9 device, const std::string &path, int index);
	void Render();
	void Clean();
private:
	LPDIRECT3DDEVICE9 m_device;
	LPD3DXMESH m_mesh;
	LPDIRECT3DTEXTURE9 *m_meshTextures;
	D3DMATERIAL9 *m_meshMaterials;
	DWORD m_materialCount;
};

SE_END_NAMESPACE

#endif