#include "ResourceManager.h"

SE_BEGIN_NAMESPACE

void ResourceManager::Init(LPDIRECT3DDEVICE9 device) {
	m_device = device;
}

void ResourceManager::AddMesh(std::string path) {
	Mesh mesh;
	mesh.Load(m_device, path);
	m_meshes.push_back(mesh);
}

void ResourceManager::Render() {
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_meshes[i].Render();
	}
}

void ResourceManager::Clean() {
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_meshes[i].Clean();
	}
	m_meshes.clear();
}

SE_END_NAMESPACE