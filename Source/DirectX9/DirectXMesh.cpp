#include "DirectX9\DirectXMesh.h"

namespace se {

	Mesh::Mesh(const std::string &path) {
		m_path = path;
	}

	void Mesh::Create() {
		m_mesh = nullptr;
		m_meshMaterials = nullptr;
		m_meshTextures = nullptr;
		m_materialCount = 0;
		m_logger.SelectLogger("engine.log");
	}

	void Mesh::Load() {
		LPD3DXBUFFER materialBuffer;
		if (FAILED(D3DXLoadMeshFromX(m_path.c_str(), D3DXMESH_SYSTEMMEM, Direct3D::GetDevice(), NULL, &materialBuffer, NULL, &m_materialCount, &m_mesh))) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to load mesh: " + m_path + " count: " + std::to_string(m_materialCount));
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
					m_logger.Log(2, __FILE__, __LINE__, "Could not find texture map path: " + src);
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
			Direct3D::GetDevice()->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			Direct3D::GetDevice()->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
			Direct3D::GetDevice()->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			Direct3D::GetDevice()->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			Direct3D::GetDevice()->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
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