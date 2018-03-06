#include "Model.h"

namespace se {

	Model::Model(AbstractRenderer *renderer, const std::string &assetName, const std::string &path) : AbstractAsset(renderer, assetName) {
		m_renderer->CreateMesh(m_assetName, path);
	}

	void Model::Render() {
		m_renderer->Render(m_assetName);
	}

	void Model::Release() {
		m_renderer->Release(m_assetName);
	}

}