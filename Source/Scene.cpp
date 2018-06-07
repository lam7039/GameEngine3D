#include "Scene.h"
#include "Asset.h"
#include "AssetManager.h"
#include <algorithm>

namespace se {

	void Scene::AddEntity(Entity *entity) {
		m_entities.push_back(entity);
	}

	void Scene::Update(float delta) {
		int entityCount = m_entities.size();
		if (entityCount == 0) {
			return;
		}
		for (int i = 0; i < entityCount; i++) {
			m_entities[i]->Update(delta);
			// Set the target position to the camera position for the skybox to follow.
			if (m_entities[i]->GetEntityType() == ENTITYTYPE_CAMERA) {
				m_targetPosition = m_entities[i]->GetPosition();
			}
			if (m_entities[i]->GetEntityType() == ENTITYTYPE_SKYBOX) {
				m_entities[i]->SetPosition(m_targetPosition);
			}
		}
	}

	void Scene::Remove(Entity *entity) {
		// Erase the object from the list and to avoid gaps I use remove.
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
	}

	void Scene::Remove() {
		for (auto i : m_entities) {
			delete i;
		}
		m_entities.clear();
	}

	const std::vector<Entity*> &Scene::GetEntities() const {
		return m_entities;
	}

}
