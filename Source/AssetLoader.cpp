#include "AssetLoader.h"

namespace se {

	AssetLoader *AssetLoader::m_instance = nullptr;

	AssetLoader::AssetLoader() {
		m_instance = nullptr;
	}

	AssetLoader::~AssetLoader() {
		std::unordered_map<std::string, Mesh*>::iterator it;
		for (it = m_meshes.begin(); it != m_meshes.end(); it++) {
			ReleaseMesh(it->first);
		}
	}

	AssetLoader *AssetLoader::GetInstance() {
		if (m_instance == nullptr) {
			m_instance = new AssetLoader();
		}
		return m_instance;
	}

	void AssetLoader::AddMesh(const std::string &path) {
		Mesh *mesh = new Mesh("Assets\\" + path);
		mesh->Load();
		m_meshes[path] = mesh;
	}

	std::unordered_map<std::string, Mesh*> AssetLoader::GetMeshes() {
		return m_meshes;
	}

	void AssetLoader::ReleaseMesh(const std::string &filename) {
		m_meshes[filename]->Release();
		m_meshes.erase(filename);
	}

	/* void LoadAsset(const std::string &path) {
		std::string extension = "";
		int pos = path.find_last_of(".");
		if (pos != std::string::npos) {
			extension = path.substr(pos + 1);
		}
		if (extension == "x") {
			AssetLoader::GetInstance()->AddMesh(path);
		}
	}*/

}
