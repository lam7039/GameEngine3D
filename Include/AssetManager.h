#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <unordered_map>
#include "Asset.h"

namespace se {

	///
	/// With this manager you can add, get and release assets
	///
	class AssetManager {
	public:
		///
		/// Add an asset with a name to refer it by
		///
		void AddAsset(const std::string &name, AbstractAsset *asset);
		///
		/// Release an asset with the referred name 
		///
		void ReleaseAsset(const std::string &name);
		///
		/// Get the initiated instance of AssetManager to use its methods
		///
		static AssetManager *GetInstance();
		///
		/// Get all assets in an unordered_map
		///
		std::unordered_map<std::string, AbstractAsset*> GetAssetList();
	private:
		static AssetManager *m_instance;
		std::unordered_map<std::string, AbstractAsset*> m_assets;
		AssetManager();
		~AssetManager();
	};

}

#endif