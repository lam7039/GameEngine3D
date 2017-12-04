#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "std.h"
#include "Scene.h"
#include <map>

SE_BEGIN_NAMESPACE

class SceneLoader {
public:
	SE_API static SceneLoader *GetInstance();
	SE_API static Scene *GetCurrentScene();
	SE_API Scene *GetScene(const std::string &name);
	SE_API void AddScene(const std::string &name);
	SE_API void SetCurrentScene(const std::string &name);
private:
	static SceneLoader *m_instance;
	static Scene *m_currentScene;
	std::map<std::string, Scene> m_scenes;
	SceneLoader();

};

SE_END_NAMESPACE

#endif