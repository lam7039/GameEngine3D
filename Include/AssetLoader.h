#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Asset.h"

namespace se {

	class AssetLoader {
	public:
		void AddAsset(const std::string &name, AbstractAsset *asset);
		void ReleaseAsset(const std::string &filename);
		static AssetLoader *GetInstance();
		std::unordered_map<std::string, AbstractAsset*> GetAssetList();
	private:
		static AssetLoader *m_instance;
		std::unordered_map<std::string, AbstractAsset*> m_assets;
		AssetLoader();
		~AssetLoader();
	};

}

#endif