#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "Debug.h"
#include "Asset.h"
#include "Renderer.h"

namespace se {

	///
	/// A default model asset.
	///
	class Model : public AbstractAsset {
	public:
		///
		/// Create a model with a renderer and the path to the model you want to load.
		///
		Model(AbstractRenderer *renderer, const std::string &assetName, const std::string &path);
		///
		/// Render the model asset.
		///
		void Render();
		///
		/// Release the model asset.
		///
		void Release();
	private:
		Debug m_logger;
	};

}

#endif