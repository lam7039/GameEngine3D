#include "EntityDerived.h"
#include "AssetManager.h"

namespace se {

	EntityDerived::EntityDerived() {
		m_assetName = "";
		m_entityType = ENTITYTYPE_NOTYPE;
		SetScale(1.0f, 1.0f, 1.0f);
	}

	void EntityDerived::Update(float delta) {
	}

	void EntityDerived::Render(AbstractRenderer *renderer) {
		renderer->SetFVF(true, false, false, true);
		renderer->SetStreamSource(0, m_assetName, 0);
		renderer->SetTexture(0, m_assetName, 0);
		renderer->Draw(m_assetName);
	}

}