#include "SceneLoader.h"

SE_BEGIN_NAMESPACE

SceneLoader *SceneLoader::m_instance = nullptr;
Scene *SceneLoader::m_currentScene = nullptr;

SceneLoader::SceneLoader() {
	m_scenes = std::map<std::string, Scene>();
}

SE_API SceneLoader *SceneLoader::GetInstance() {
	if (m_instance == nullptr) {
		m_instance = new SceneLoader();
	}
	return m_instance;
}

SE_API Scene *SceneLoader::GetCurrentScene() {
	return m_currentScene;
}

SE_API void SceneLoader::AddScene(const std::string &name) {
	m_scenes[name] = Scene();
	if (m_currentScene == nullptr) {
		m_currentScene = &m_scenes[name];
	}
}

SE_API void SceneLoader::SetCurrentScene(const std::string &name) {
	m_currentScene = &m_scenes[name];
}

SE_API Scene *SceneLoader::GetScene(const std::string &name) {
	return &m_scenes[name];
}

SE_END_NAMESPACE