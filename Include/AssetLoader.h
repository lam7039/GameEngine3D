#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "std.h"
#include "Asset.h"

namespace se {

	class AssetLoader {
	public:
		void AddMesh(const std::string &path);
		void AddTerrain(const std::string &heightMap, const std::string &texture);
		void ReleaseMesh(const std::string &filename);
		static AssetLoader *GetInstance();
		std::unordered_map<std::string, AbstractAsset*> GetAssets();
	private:
		static AssetLoader *m_instance;
		std::unordered_map<std::string, AbstractAsset*> m_assets;
		AssetLoader();
		~AssetLoader();
	};

}

#endif