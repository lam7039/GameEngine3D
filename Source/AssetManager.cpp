#include "AssetManager.h"

namespace se {

	AssetManager *AssetManager::m_instance = nullptr;

	AssetManager::AssetManager() {
		m_instance = nullptr;
	}

	AssetManager::~AssetManager() {
		for (auto &i : m_assets) {
			ReleaseAsset(i.first);
		}
	}

	AssetManager *AssetManager::GetInstance() {
		if (!m_instance) {
			m_instance = new AssetManager();
		}
		return m_instance;
	}

	void AssetManager::AddAsset(const std::string &name, AbstractAsset *model) {
		if (m_assets.find(name) != m_assets.end()) {
			return;
		}
		m_assets[name] = model;
	}

	void AssetManager::ReleaseAsset(const std::string &name) {
		if (m_assets.find(name) != m_assets.end()) {
			return;
		}
		m_assets[name]->Release();
		m_assets.erase(name);
	}

	AbstractAsset* AssetManager::GetAsset(const std::string &name) {
		if (m_assets.find(name) == m_assets.end()) {
			return nullptr;
		}
		return m_assets[name];
	}

}
