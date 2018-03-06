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
	/// With this interface you can create your own terrain to load into a Scene
	///
	class Terrain : public AbstractAsset {
	public:
		Terrain(AbstractRenderer *renderer, const std::string &assetName, const std::string &heightMap, const std::string &texture);
		void Render();
		void Release();
	private:
		Debug m_logger;
		Bitmap m_bitmap;
		Vector3i m_size;
	};

}

#endif