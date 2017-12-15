#include "Scene.h"
//TODO: fix abstraction so terrain doesn't get called here
#include "DirectX9\DirectXTerrain.h"
#include <algorithm>

namespace se {

	Scene::Scene() {
		m_terrain = new Terrain();
		m_terrain->Create();
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
		int entityCount = m_entities.size();
		if (entityCount > 0) {
			for (int i = 0; i < entityCount; i++) {
				m_entities[i]->Render();
			}
		}
		m_terrain->Process();
	}

	void Scene::Release() {
		m_terrain->Release();
	}

	const std::vector<Entity*> &Scene::GetEntities() const {
		return m_entities;
	}

}
