#ifndef SKYBOX_H
#define SKYBOX_H

#include "Vector3.h"
#include "Asset.h"
#include "Renderer.h"
#include "Debug.h"

namespace se {

	///
	/// with this interface you can create your own skybox to load into a Scene
	///
	class Skybox : public AbstractAsset {
	public:
		Skybox(AbstractRenderer *renderer, const std::string &assetName, const std::string &src);
		void Render();
		void Release();
	private:
		Debug m_logger;
		Vector3i m_size;
	};

}

#endif