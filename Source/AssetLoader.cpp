#include <d3dx9.h>
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

AssetLoader *AssetLoader::m_instance = nullptr;

AssetLoader::AssetLoader() {
	m_instance = nullptr;
}

AssetLoader *AssetLoader::GetInstance() {
	if (m_instance == nullptr) {
		m_instance = new AssetLoader();
	}
	return m_instance;
}

void AssetLoader::Init(LPDIRECT3DDEVICE9 device) {
	m_device = device;
}

void AssetLoader::AddMesh(const std::string &filename) {
	Mesh mesh;
	mesh.Load(m_device, "Assets\\" + filename);
	m_meshes[filename] = mesh;
}

std::map<std::string, Mesh> *AssetLoader::GetMeshes() {
	return &m_meshes;
}

void AssetLoader::Clean(const std::string &filename) {
	m_meshes[filename].Clean();
	m_meshes.erase(filename);
}

SE_END_NAMESPACE