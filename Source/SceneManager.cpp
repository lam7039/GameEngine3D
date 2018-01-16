#include "SceneManager.h"
#include <Windows.h>

namespace se {

	SceneManager *SceneManager::m_instance = nullptr;
	Scene *SceneManager::m_currentScene = nullptr;

	SceneManager::SceneManager() {
		m_scenes = std::unordered_map<std::string, Scene>();
		m_logger.SelectLogger("engine.log");
	}

	SceneManager *SceneManager::GetInstance() {
		if (m_instance == nullptr) {
			m_instance = new SceneManager();
		}
		return m_instance;
	}

	Scene *SceneManager::GetCurrentScene() {
		return m_currentScene;
	}

	void SceneManager::AddScene(const std::string &name) {
		if (m_scenes.find(name) != m_scenes.end()) {
			m_logger.Log(2, __FILE__, __LINE__, "Scene already exists");
			return;
		}
		m_scenes[name] = Scene();
		if (m_currentScene == nullptr) {
			m_currentScene = &m_scenes[name];
		}
	}

	void SceneManager::SetCurrentScene(const std::string &name) {
		m_currentScene = &m_scenes[name];
	}

	Scene *SceneManager::GetScene(const std::string &name) {
		return &m_scenes[name];
	}

	int SceneManager::GetSceneCount() {
		return m_scenes.size();
	}

}