#include "Scene.h"

SE_BEGIN_NAMESPACE

Scene::Scene() {
	m_objects = std::vector<Object>();
}

void Scene::AddObject(Object object) {
	m_objects.push_back(object);
}

SE_END_NAMESPACE