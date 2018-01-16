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
		void SetTerrain(AbstractTerrain *terrain);
		void SetSkybox(AbstractSkybox *skybox);
		void AddEntity(Entity *entity);
		void RemoveEntity(Entity *entity);
		void Update(float delta);
		void Render();
		void Release();
		const std::vector<Entity*> &GetEntities() const;
	private:
		std::vector<Entity*> m_entities;
		AbstractTerrain *m_terrain;
		AbstractSkybox *m_skybox;
	};

}

#endif