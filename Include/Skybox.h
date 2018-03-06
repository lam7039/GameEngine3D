#ifndef SKYBOX_H
#define SKYBOX_H

#include "Vector3.h"
#include "Asset.h"
#include "Renderer.h"
#include "Debug.h"

namespace se {

	///
	/// A default skybox asset.
	///
	class Skybox : public AbstractAsset {
	public:
		///
		/// Create a skybox with a renderer and a cubemap.
		///
		Skybox(AbstractRenderer *renderer, const std::string &assetName, const std::string &src);
		///
		/// Render the skybox asset.
		///
		void Render();
		///
		/// Release the skybox asset.
		///
		void Release();
	private:
		Debug m_logger;
		Vector3i m_size;
	};

}

#endif