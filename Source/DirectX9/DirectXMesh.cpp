#include "DirectX9\DirectXMesh.h"

namespace se {

	Mesh::Mesh(LPDIRECT3DDEVICE9 device, const std::string &path) {
		m_path = path;
		m_device = device;
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
		if (FAILED(D3DXLoadMeshFromX(m_path.c_str(), D3DXMESH_SYSTEMMEM, m_device, NULL, &materialBuffer, NULL, &m_materialCount, &m_mesh))) {
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
				if (FAILED(D3DXCreateTextureFromFile(m_device, src.c_str(), &m_meshTextures[i]))) {
					m_logger.Log(2, __FILE__, __LINE__, "Could not find texture map path: " + src);
					return;
				}
			}
		}
		materialBuffer->Release();
	}

	void Mesh::Process() {
		for (DWORD i = 0; i < m_materialCount; i++) {
			m_device->SetMaterial(&m_meshMaterials[i]);
			m_device->SetTexture(i, m_meshTextures[i]);
			m_device->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
			m_device->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
			m_device->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			m_device->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			m_device->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
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