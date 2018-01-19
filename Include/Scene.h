#ifndef SCENE_H
#define SCENE_H

#include "std.h"
#include "Entity.h"
#include "Asset.h"
#include "Terrain.h"
#include "Skybox.h"

namespace se {

	class Scene {
	public:
		///
		/// Set the terrain you want to use
		///
		void SetTerrain(AbstractTerrain *terrain);
		///
		/// Set the skybox you want to use
		///
		void SetSkybox(AbstractSkybox *skybox);
		///
		/// Transform the skybox
		///
		void SetSkyboxTransform(Transform3f *transform);
		///
		/// Add an entity to the scene
		///
		void AddEntity(Entity *entity);
		///
		/// Remove an entity from the scene
		///
		void RemoveEntity(Entity *entity);
		void Update(float delta);
		void Process();
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
		AbstractTerrain *m_terrain;
		AbstractSkybox *m_skybox;
		Transform3f *m_targetPos;
	};

}

#endif