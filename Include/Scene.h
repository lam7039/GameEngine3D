#ifndef SCENE_H
#define SCENE_H

#include "std.h"
#include "Object.h"
#include <vector>

SE_BEGIN_NAMESPACE

class Scene {
public:
	Scene();
	void AddObject(Object object);
private:
	std::vector<Object> m_objects;
};

SE_END_NAMESPACE

#endif