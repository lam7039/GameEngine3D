#ifndef SCENE_H
#define SCENE_H

#include "std.h"
#include "Entity.h"
#include <vector>

SE_BEGIN_NAMESPACE

//TODO: use export on interfaces, not on classes itself
class Scene {
public:
	Scene();
	SE_API void AddEntity(Entity *entity);
	SE_API void RemoveEntity(Entity *entity);
	void Update(float delta);
	void Render();
	std::vector<Entity*> GetEntities();
private:
	std::vector<Entity*> m_entities;
};

SE_END_NAMESPACE

#endif