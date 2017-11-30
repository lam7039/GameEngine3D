#include "ResourceManager.h"

SE_BEGIN_NAMESPACE

void ResourceManager::Init(LPDIRECT3DDEVICE9 device) {
	m_device = device;
	m_meshCount = 0;
}

void ResourceManager::AddMesh(std::string path) {
	Mesh mesh;
	mesh.Load(m_device, path, m_meshCount);
	m_meshes.push_back(mesh);
	m_meshCount++;
}

std::vector<Mesh> ResourceManager::GetMeshes() {
	return m_meshes;
}

void ResourceManager::Clean() {
	for (unsigned int i = 0; i < m_meshes.size(); i++) {
		m_meshes[i].Clean();
	}
	m_meshes.clear();
}

SE_END_NAMESPACE