#ifndef ABSTRACTTERRAIN_H
#define ABSTRACTTERRAIN_H

#include <string>
#include "Asset.h"
#include "Bitmap.h"
#include "Debug.h"
#include "Renderer.h"
#include "Vector3.h"

namespace se {

	///
	/// A default terrain asset.
	///
	class Terrain : public AbstractAsset {
	public:
		///
		/// Create a terrain with a renderer, heightmap for the heights and texture to put on the terrain.
		///
		Terrain(AbstractRenderer *renderer, const std::string &assetName, const std::string &heightMap, const std::string &texture);
	private:
		Debug m_logger;
		Bitmap m_bitmap;
		Vector3i m_size;
	};

}

#endif