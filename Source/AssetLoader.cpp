#include "AssetLoader.h"

namespace se {

	AssetLoader *AssetLoader::m_instance = nullptr;

	AssetLoader::AssetLoader() {
		m_instance = nullptr;
	}

	AssetLoader::~AssetLoader() {
		for (auto &i : m_assets) {
			ReleaseAsset(i.first);
		}
	}

	AssetLoader *AssetLoader::GetInstance() {
		if (!m_instance) {
			m_instance = new AssetLoader();
		}
		return m_instance;
	}

	void AssetLoader::AddAsset(const std::string &name, AbstractAsset *asset) {
		asset->Create();
		asset->Load();
		m_assets[name] = asset;
	}

	std::unordered_map<std::string, AbstractAsset*> AssetLoader::GetAssetList() {
		return m_assets;
	}

	void AssetLoader::ReleaseAsset(const std::string &filename) {
		m_assets[filename]->Release();
		m_assets.erase(filename);
	}

}
