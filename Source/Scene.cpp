#include "Scene.h"
#include <algorithm>

namespace se {

	void Scene::SetTerrain(AbstractTerrain *terrain) {
		m_terrain = terrain;
	}

	void Scene::SetSkybox(AbstractSkybox *skybox) {
		m_skybox = skybox;
	}

	void Scene::AddEntity(Entity *entity) {
		m_entities.push_back(entity);
	}

	void Scene::RemoveEntity(Entity *entity) {
		//Erase the object from the list and to avoid gaps I use remove
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
	}

	void Scene::Update(float delta) {
		int entityCount = m_entities.size();
		if (entityCount == 0) {
			return;
		}
		for (int i = 0; i < entityCount; i++) {
			m_entities[i]->Update(delta);
		}
	}

	void Scene::Render() {
		if (m_terrain) {
			m_terrain->Process();
		}
		if (m_skybox) {
			m_skybox->Process();
		}
	}

	void Scene::Release() {
		if (m_terrain) {
			m_terrain->Release();
		}
		if (m_skybox) {
			m_skybox->Release();
		}
	}

	const std::vector<Entity*> &Scene::GetEntities() const {
		return m_entities;
	}

}
