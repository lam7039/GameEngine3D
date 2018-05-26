#include "Model.h"

namespace se {

	Model::Model(AbstractRenderer *renderer, const std::string &assetName, const std::string &path) : AbstractAsset(renderer, assetName) {
		m_renderer->CreateMesh(m_assetName, path);
	}

	void Model::Render() {
		m_renderer->SetSamplerState(0, SAMP_MIPFILTER, TEXF_LINEAR);
		m_renderer->DrawMesh(m_assetName);
	}

	void Model::Release() {
		m_renderer->Release(m_assetName);
	}

}