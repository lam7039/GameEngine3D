#ifndef SCENE_H
#define SCENE_H

#include "std.h"
#include "Object.h"
#include <vector>

SE_BEGIN_NAMESPACE

class Scene {
public:
	Scene();
	SE_API void AddObject(Object *object);
	SE_API void RemoveObject(Object *object);
	void Update(float delta);
	void Render();
	std::vector<Object*> GetObjects();
private:
	std::vector<Object*> m_objects;
};

SE_END_NAMESPACE

#endif