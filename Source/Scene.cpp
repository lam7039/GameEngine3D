#include "Scene.h"
#include <algorithm>

namespace se {

	Scene::Scene() {
	}

	void Scene::AddEntity(Entity *entity) {
		m_entities.push_back(entity);
	}

	void Scene::RemoveEntity(Entity *entity) {
		//Erase the object from the list and to avoid gaps I use remove
		m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), entity), m_entities.end());
	}

	void Scene::Update(float delta) {
		if (m_entities.size() == 0) {
			return;
		}
		for (int i = 0; i < m_entities.size(); i++) {
			m_entities[i]->Update(delta);
		}
	}

	void Scene::Render() {
		if (m_entities.size() == 0) {
			return;
		}
		for (int i = 0; i < m_entities.size(); i++) {
			m_entities[i]->Render();
		}
	}

	const std::vector<Entity*> &Scene::GetEntities() const {
		return m_entities;
	}

}
