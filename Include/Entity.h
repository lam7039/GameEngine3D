#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Vector3.h"

namespace se {

	enum EntityType {
		ENTITYTYPE_NOTYPE,
		ENTITYTYPE_SKYBOX,
		ENTITYTYPE_TERRAIN,
		ENTITYTYPE_MODEL,
		ENTITYTYPE_CAMERA
	};

	///
	/// This interface is what you're inheriting to create new entities to load them in SceneManager
	///
	class Entity {
	public:
		Entity();
		void SetPosition(float x, float y, float z);
		void SetPosition(Vector3f position);
		void SetScale(float x, float y, float z);
		void SetScale(Vector3f scale);
		void SetRotation(float x, float y, float z);
		void SetRotation(Vector3f rotation);
		void SetAssetName(const std::string &assetName);
		void SetEntityType(EntityType type);
		std::string GetAssetName() const;
		EntityType GetEntityType() const;
		virtual void Update(float delta);
		virtual void Release();
		Vector3f *GetPosition();
		Vector3f *GetScale();
		Vector3f *GetRotation();
	protected:
		std::string m_assetName;
		EntityType m_entityType;
		Vector3f m_position;
		Vector3f m_scale;
		Vector3f m_rotation;
	};

}

#endif