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

	void EntityDerived::Render() {
		AssetManager::GetInstance()->GetAsset(m_assetName)->Render();
	}

	void EntityDerived::Release() {
		AssetManager::GetInstance()->GetAsset(m_assetName)->Release();
	}

}