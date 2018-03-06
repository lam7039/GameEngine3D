#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Entity.h"

namespace se {

	class Scene {
	public:
		///
		/// Add an entity to the scene.
		///
		void AddEntity(Entity *entity);
		///
		/// Update all entities
		///
		void Update(float delta);
		///
		/// Remove an entity from the scene.
		///
		void Remove(Entity *entity);
		///
		/// Remove everything from the scene
		///
		void Remove();
		///
		/// Get all entities in the scene
		///
		const std::vector<Entity*> &GetEntities() const;
	private:
		std::vector<Entity*> m_entities;
		Vector3f *m_targetPosition;
	};

}

#endif