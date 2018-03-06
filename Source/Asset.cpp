#include "Asset.h"

namespace se {

	AbstractAsset::AbstractAsset(AbstractRenderer *renderer, const std::string &assetName) {
		m_renderer = renderer;
		m_assetName = assetName;
	}

	std::string AbstractAsset::GetAssetName() const {
		return m_assetName;
	}

}