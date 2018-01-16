#include "Entity.h"

namespace se {

	Entity::Entity() {
		m_entityName = "";
		m_assetName = "";
	}

	void Entity::Update(float delta) {
	}

	void Entity::SetScale(float scale) {
		m_transform.scaleX = scale;
		m_transform.scaleY = scale;
		m_transform.scaleZ = scale;
	}

	void Entity::SetRotation(float x, float y, float z) {
		m_transform.rotX = x;
		m_transform.rotY = y;
		m_transform.rotZ = z;
	}

	void Entity::SetPosition(float x, float y, float z) {
		m_transform.posX = x;
		m_transform.posY = y;
		m_transform.posZ = z;
	}

	Transform3f Entity::GetTarget() const {
		return m_transform;
	}

	std::string Entity::GetEntityName() const {
		return m_entityName;
	}

	std::string Entity::GetAssetName() const {
		return m_assetName;
	}

}
