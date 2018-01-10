#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "std.h"
#include "Scene.h"
#include "Debug.h"

namespace se {

	class SceneLoader {
	public:
		static SceneLoader *GetInstance();
		static Scene *GetCurrentScene();
		Scene *GetScene(const std::string &name);
		void AddScene(const std::string &name);
		void SetCurrentScene(const std::string &name);
	private:
		Debug m_logger;
		static SceneLoader *m_instance;
		static Scene *m_currentScene;
		std::unordered_map<std::string, Scene> m_scenes;
		SceneLoader();

	};

}

#endif