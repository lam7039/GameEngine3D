#include <d3dx9.h>
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

AssetLoader *AssetLoader::m_instance = nullptr;

AssetLoader::AssetLoader() {
	m_instance = nullptr;
}

AssetLoader::~AssetLoader() {
	std::map<std::string, Mesh>::iterator it;
	for (it = m_meshes.begin(); it != m_meshes.end(); it++) {
		ReleaseMesh(it->first);
	}
}

SE_API AssetLoader *AssetLoader::GetInstance() {
	if (m_instance == nullptr) {
		m_instance = new AssetLoader();
	}
	return m_instance;
}

void AssetLoader::Init(LPDIRECT3DDEVICE9 device) {
	m_device = device;
}

SE_API void AssetLoader::AddMesh(const std::string &path) {
	Mesh mesh;
	mesh.Load(m_device, "Assets\\" + path);
	m_meshes[path] = mesh;
}

std::map<std::string, Mesh> *AssetLoader::GetMeshes() {
	return &m_meshes;
}

void AssetLoader::ReleaseMesh(const std::string &filename) {
	m_meshes[filename].Release();
	m_meshes.erase(filename);
}

/*SE_API void LoadAsset(const std::string &path) {
	std::string extension = "";
	int pos = path.find_last_of(".");
	if (pos != std::string::npos) {
		extension = path.substr(pos + 1);
	}
	if (extension == "x") {
		AssetLoader::GetInstance()->AddMesh(path);
	}
}

SE_API void ReleaseAsset(const std::string &path) {
	AssetLoader::GetInstance()->Release(path);
}*/

SE_END_NAMESPACE