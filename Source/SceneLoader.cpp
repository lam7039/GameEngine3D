#include "SceneLoader.h"
#include <Windows.h>

namespace se {

	SceneLoader *SceneLoader::m_instance = nullptr;
	Scene *SceneLoader::m_currentScene = nullptr;

	SceneLoader::SceneLoader() {
		m_scenes = std::map<std::string, Scene>();
	}

	SceneLoader *SceneLoader::GetInstance() {
		if (m_instance == nullptr) {
			m_instance = new SceneLoader();
		}
		return m_instance;
	}

	Scene *SceneLoader::GetCurrentScene() {
		return m_currentScene;
	}

	void SceneLoader::AddScene(const std::string &name) {
		if (m_scenes.find(name) != m_scenes.end()) {
			//MessageBox(NULL, "scene already exists", "sceneloader", MB_OK); //Instead of this, log it
			return;
		}
		m_scenes[name] = Scene();
		if (m_currentScene == nullptr) {
			m_currentScene = &m_scenes[name];
		}
	}

	void SceneLoader::SetCurrentScene(const std::string &name) {
		m_currentScene = &m_scenes[name];
	}

	Scene *SceneLoader::GetScene(const std::string &name) {
		return &m_scenes[name];
	}

}