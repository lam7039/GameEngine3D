#include "DirectX9\DirectXMesh.h"

namespace se {

	Mesh::Mesh(const std::string &path) {
		m_path = path;
		m_mesh = nullptr;
		m_meshMaterials = nullptr;
		m_meshTextures = nullptr;
		m_materialCount = 0;
	}

	void Mesh::Create() {
		//
	}

	void Mesh::Load() {
		LPD3DXBUFFER materialBuffer;
		if (FAILED(D3DXLoadMeshFromX(m_path.c_str(), D3DXMESH_SYSTEMMEM, Direct3D::GetDevice(), NULL, &materialBuffer, NULL, &m_materialCount, &m_mesh))) {
			MessageBox(NULL, ("failed to load mesh: " + m_path + " count: " + std::to_string(m_materialCount)).c_str(), "Meshes.exe", MB_OK);
			return;
		}
		D3DXMATERIAL *materials = (D3DXMATERIAL*)materialBuffer->GetBufferPointer();
		m_meshMaterials = new D3DMATERIAL9[m_materialCount];
		m_meshTextures = new LPDIRECT3DTEXTURE9[m_materialCount];
		for (DWORD i = 0; i < m_materialCount; i++) {
			m_meshMaterials[i] = materials[i].MatD3D;
			m_meshMaterials[i].Ambient = m_meshMaterials[i].Diffuse;
			m_meshTextures[i] = NULL;
			if (materials[i].pTextureFilename != NULL && lstrlen(materials[i].pTextureFilename) > 0) {
				std::string src = "Assets\\";
				src += materials[i].pTextureFilename;
				if (FAILED(D3DXCreateTextureFromFile(Direct3D::GetDevice(), src.c_str(), &m_meshTextures[i]))) {
					MessageBox(NULL, ("Could not find texture map path: " + src).c_str(), "Meshes.exe", MB_OK);
					return;
				}
			}
		}
		materialBuffer->Release();
	}

	void Mesh::Process() {
		for (DWORD i = 0; i < m_materialCount; i++) {
			Direct3D::GetDevice()->SetMaterial(&m_meshMaterials[i]);
			Direct3D::GetDevice()->SetTexture(i, m_meshTextures[i]);
			m_mesh->DrawSubset(i);
		}
	}

	void Mesh::Release() {
		if (m_meshMaterials != NULL) {
			delete[] m_meshMaterials;
		}
		if (m_meshTextures) {
			for (DWORD i = 0; i < m_materialCount; i++) {
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

}