#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <unordered_map>
#include "Asset.h"

namespace se {

	///
	/// With this manager you can add, get and release assets.
	///
	class AssetManager {
	public:
		///
		/// Get the initiated instance of AssetManager to use its methods.
		///
		static AssetManager *GetInstance();
		///
		/// Add an asset with a name to refer it by.
		///
		void AddAsset(const std::string &name, AbstractAsset *asset);
		///
		/// Release an asset with the referred name.
		///
		void ReleaseAsset(const std::string &name);
		///
		/// Release all assets.
		///
		void ReleaseAll();
		///
		/// Get an asset with the given name
		///
		AbstractAsset* GetAsset(const std::string &name);
		/**/
		//TODO: add explanation to this method
		std::string GetCurrentAssetName() const;
		void SetCurrentAssetName(const std::string &name);
		/**/
	private:
		static AssetManager *m_instance;
		std::string m_currentAssetName;
		std::unordered_map<std::string, AbstractAsset*> m_assets;
		AssetManager();
		~AssetManager();
	};

}

#endif