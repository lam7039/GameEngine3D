#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Vector3.h"

namespace se {

	///
	/// To differentiate between entity types.
	///
	enum EntityType {
		ENTITYTYPE_NOTYPE,
		ENTITYTYPE_SKYBOX,
		ENTITYTYPE_TERRAIN,
		ENTITYTYPE_MODEL,
		ENTITYTYPE_CAMERA
	};

	///
	/// This interface is what you're inheriting to create new entities to load them in SceneManager.
	///
	class Entity {
	public:
		Entity();
		///
		/// Set the position of the entity with seperate floats.
		///
		void SetPosition(float x, float y, float z);
		///
		/// Set the position of the entity with Vector3f.
		///
		void SetPosition(Vector3f position);
		///
		/// Set the scale of the entity with seperate floats.
		///
		void SetScale(float x, float y, float z);
		///
		/// Set the scale of the entity with Vector3f.
		///
		void SetScale(Vector3f scale);
		///
		/// Set the rotation of the entity with seperate floats.
		///
		void SetRotation(float x, float y, float z);
		///
		/// Set the rotation of the entity with Vector3f.
		///
		void SetRotation(Vector3f rotation);
		///
		/// Set the name of the asset the entity is supposed to use.
		///
		void SetAssetName(const std::string &assetName);
		///
		/// Set what type of entity this entity is with EntityType.
		///
		void SetEntityType(EntityType type);
		///
		/// Get the name of the asset the entity is using.
		///
		std::string GetAssetName() const;
		///
		/// Get the EntityType of the entity.
		///
		EntityType GetEntityType() const;
		///
		/// Update the entity each frame.
		///
		virtual void Update(float delta);
		///
		/// Release related entity data.
		///
		virtual void Release();
		///
		/// Render the entity model
		///
		virtual void Render();
		///
		/// Get the current position of the entity.
		///
		Vector3f *GetPosition();
		///
		/// Get the current scale of the entity.
		///
		Vector3f *GetScale();
		///
		/// Get the current rotation of the entity.
		///
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