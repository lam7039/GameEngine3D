#ifndef ASSET_H
#define ASSET_H

#include <string>
#include "Renderer.h"

namespace se {

	///
	/// You can use this interface to create your own type of asset.
	///
	class AbstractAsset {
	public:
		///
		/// Pass the renderer you're using and the assetname you want to create an asset with to here to set the variables, otherwise you can just do it in the child class.
		///
		AbstractAsset(AbstractRenderer *renderer, const std::string &assetName);
		///
		/// Use this to release any asset that is a child of this interface.
		///
		virtual void Release() = 0;
		///
		/// Get the name of the asset.
		///
		std::string GetAssetName() const;
	protected:
		AbstractRenderer *m_renderer;
		std::string m_assetName;
	};

}

#endif
