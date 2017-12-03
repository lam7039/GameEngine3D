#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "std.h"
#include "Scene.h"
#include <map>

SE_BEGIN_NAMESPACE

class SceneLoader {
public:
	SceneLoader();
	static SceneLoader *GetInstance();
	static Scene *GetCurrentScene();
	Scene *GetScene(const std::string &name);
	void AddScene(const std::string &name);
	void SetCurrentScene(const std::string &name);
private:
	static SceneLoader *m_instance;
	static Scene *m_currentScene;
	std::map<std::string, Scene> m_scenes;

};

SE_END_NAMESPACE

#endif