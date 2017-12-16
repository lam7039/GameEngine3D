#include "AssetLoader.h"
//TODO: fix assets so mesh doesn't get called here
#include "DirectX9/DirectXMesh.h"

namespace se {

	AssetLoader *AssetLoader::m_instance = nullptr;

	AssetLoader::AssetLoader() {
		m_instance = nullptr;
	}

	AssetLoader::~AssetLoader() {
		std::unordered_map<std::string, AbstractAsset*>::iterator it = m_assets.begin();
		std::unordered_map<std::string, AbstractAsset*>::iterator end = m_assets.end();
		for (it; it != end; it++) {
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
		Mesh *mesh = new Mesh();
		mesh->SetPath("Assets\\" + path);
		mesh->Load();
		m_assets[path] = mesh;
	}

	/*void AssetLoader::AddAsset(AbstractAsset *asset) {
		asset->Load();
		m_assets[asset->name] = mesh;
	}*/

	std::unordered_map<std::string, AbstractAsset*> AssetLoader::GetAssets() {
		return m_assets;
	}

	void AssetLoader::ReleaseMesh(const std::string &filename) {
		m_assets[filename]->Release();
		m_assets.erase(filename);
	}

}
