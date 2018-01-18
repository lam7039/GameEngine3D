#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "std.h"
#include "Asset.h"

namespace se {

	///
	/// With this manager you can add assets and get and release added assets
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
		/// Get the instance of the manager
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