#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "std.h"
#include "Scene.h"

namespace se {

	class SceneLoader {
	public:
		static SceneLoader *GetInstance();
		static Scene *GetCurrentScene();
		Scene *GetScene(const std::string &name);
		void AddScene(const std::string &name);
		void SetCurrentScene(const std::string &name);
	private:
		static SceneLoader *m_instance;
		static Scene *m_currentScene;
		std::unordered_map<std::string, Scene> m_scenes;
		SceneLoader();

	};

}

#endif