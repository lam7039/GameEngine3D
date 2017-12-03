#include "Scene.h"

SE_BEGIN_NAMESPACE

Scene::Scene() {
}

void Scene::AddObject(Object object) {
	m_objects.push_back(object);
}

void Scene::Update(float delta) {
	for (int i = 0; i < m_objects.size(); i++) {
		m_objects[i].Update(delta);
	}
}

void Scene::Render() {
	for (int i = 0; i < m_objects.size(); i++) {
		m_objects[i].Render();
	}
}

std::vector<Object> Scene::GetObjects() {
	return m_objects;
}

SE_END_NAMESPACE