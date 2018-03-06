#ifndef MODEL_H
#define MODEL_H

#include <string>
#include "Debug.h"
#include "Asset.h"
#include "Renderer.h"

namespace se {

	class Model : public AbstractAsset {
	public:
		Model(AbstractRenderer *renderer, const std::string &assetName, const std::string &path);
		void Render();
		void Release();
	private:
		Debug m_logger;
	};

}

#endif