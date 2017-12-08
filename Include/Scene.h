#ifndef SCENE_H
#define SCENE_H

#include "std.h"
#include "Entity.h"
#include <vector>

namespace se {

	//TODO: use export on interfaces, not on classes itself
	class Scene {
	public:
		Scene();
		void AddEntity(Entity *entity);
		void RemoveEntity(Entity *entity);
		void Update(float delta);
		void Render();
		std::vector<Entity*> GetEntities();
	private:
		std::vector<Entity*> m_entities;
	};

}

#endif