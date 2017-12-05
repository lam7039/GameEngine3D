#include "Scene.h"
#include <algorithm>

SE_BEGIN_NAMESPACE

Scene::Scene() {
}

SE_API void Scene::AddObject(Object *object) {
	m_objects.push_back(object);
}

SE_API void Scene::RemoveObject(Object *object) {
	//Erase the object from the list and to avoid gaps I use remove
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::Update(float delta) {
	if (m_objects.size() == 0) {
		return;
	}
	for (int i = 0; i < m_objects.size(); i++) {
		m_objects[i]->Update(delta);
	}
}

void Scene::Render() {
	if (m_objects.size() == 0) {
		return;
	}
	for (int i = 0; i < m_objects.size(); i++) {
		m_objects[i]->Render();
	}
}

std::vector<Object*> Scene::GetObjects() {
	return m_objects;
}

SE_END_NAMESPACE