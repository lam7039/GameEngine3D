#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <unordered_map>
#include "Scene.h"
#include "Debug.h"

namespace se {

	class SceneManager {
	public:
		///
		/// Get the initiated instance of SceneManager to use its methods
		///
		static SceneManager *GetInstance();
		///
		/// Get the current active scene 
		///
		static Scene *GetCurrentScene();
		///
		/// Get a specific scene with the scene name
		///
		Scene *GetScene(const std::string &name);
		///
		/// Add a scene
		///
		void AddScene(const std::string &name);
		///
		/// Set the current scene with the name of the scene 
		///
		void SetCurrentScene(const std::string &name);
		///
		/// Remove a specific scene with the name of the scene 
		///
		void RemoveScene(const std::string &name);
		///
		/// Remove all scenes
		///
		void RemoveAll();
		///
		/// Get the amount of scenes
		///
		int GetSceneCount();
	private:
		Debug m_logger;
		static SceneManager *m_instance;
		static Scene *m_currentScene;
		std::unordered_map<std::string, Scene> m_scenes;
		SceneManager();
	};

}

#endif