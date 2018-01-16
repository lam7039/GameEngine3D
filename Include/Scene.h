#ifndef SCENE_H
#define SCENE_H

#include "std.h"
#include "Entity.h"
#include "Asset.h"
#include "Terrain.h"
//TODO: fix abstraction for skybox
#include "DirectX9\DirectXSkybox.h"

namespace se {

	class Scene {
	public:
		Scene();
		void SetTerrain(AbstractTerrain *terrain);
		void AddEntity(Entity *entity);
		void RemoveEntity(Entity *entity);
		void Update(float delta);
		void Render();
		void Release();
		const std::vector<Entity*> &GetEntities() const;
	private:
		std::vector<Entity*> m_entities;
		AbstractTerrain *m_terrain;
		Skybox *m_skybox;
	};

}

#endif