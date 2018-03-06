#ifndef ASSET_H
#define ASSET_H

#include <string>
#include "Renderer.h"

namespace se {

	class AbstractAsset {
	public:
		AbstractAsset(AbstractRenderer *renderer, const std::string &assetName);
		virtual void Render() = 0;
		virtual void Release() = 0;
		std::string GetAssetName() const;
	protected:
		AbstractRenderer *m_renderer;
		std::string m_assetName;
	};

}

#endif
