#include "Mesh.h"

SE_BEGIN_NAMESPACE

Mesh::Mesh() {
	m_mesh = nullptr;
	m_meshMaterials = nullptr;
	m_meshTextures = nullptr;
	m_materialCount = 0;
}

void Mesh::Load(LPDIRECT3DDEVICE9 device, const std::string &path) {
	m_d3dDev = device;
	LPD3DXBUFFER materialBuffer;
	if (FAILED(D3DXLoadMeshFromX(path.c_str(), D3DXMESH_SYSTEMMEM, m_d3dDev, NULL, &materialBuffer, NULL, &m_materialCount, &m_mesh))) {
		return;
	}
	D3DXMATERIAL* materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
	m_meshMaterials = new D3DMATERIAL9[m_materialCount];
	if (m_meshMaterials == NULL) {
		return;
	}
	m_meshTextures = new LPDIRECT3DTEXTURE9[m_materialCount];
	if (m_meshTextures == NULL) {
		return;
	}
	for (unsigned long i = 0; i < m_materialCount; i++) {
		m_meshMaterials[i] = materials[i].MatD3D;
		m_meshMaterials[i].Ambient = m_meshMaterials[i].Diffuse;
		m_meshTextures[i] = NULL;
		if (materials[i].pTextureFilename != NULL && lstrlen(materials[i].pTextureFilename) > 0) {
			if (FAILED(D3DXCreateTextureFromFile(m_d3dDev, materials[i].pTextureFilename, &m_meshTextures[i]))) {
				MessageBox(NULL, "Could not find texture map", "Meshes.exe", MB_OK);
				return;
			}
		}
	}
	materialBuffer->Release();
}

void Mesh::Render() {
	for (unsigned long i = 0; i < m_materialCount; i++) {
		m_d3dDev->SetMaterial(&m_meshMaterials[i]);
		m_d3dDev->SetTexture(0, m_meshTextures[i]);
		m_mesh->DrawSubset(i);
	}
}

void Mesh::Clean() {
	if (m_meshMaterials != NULL) {
		delete[] m_meshMaterials;
	}
	if (m_meshTextures) {
		for (unsigned long i = 0; i < m_materialCount; i++) {
			if (m_meshTextures[i]) {
				m_meshTextures[i]->Release();
			}
		}
		delete[] m_meshTextures;
	}
	if (m_mesh != NULL) {
		m_mesh->Release();
	}
}

SE_END_NAMESPACE