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
		///
		/// Update the entity each frame.
		///
		virtual void Update(float delta) = 0;
		///
		/// Render the entity model
		///
		virtual void Render() = 0;
		///
		/// Release related entity data.
		///
		virtual void Release() = 0;
		///
		/// Set the position of the entity with seperate floats.
		///
		virtual void SetPosition(float x, float y, float z);
		///
		/// Set the position of the entity with Vector3f.
		///
		virtual void SetPosition(Vector3f position);
		///
		/// Set the scale of the entity with seperate floats.
		///
		virtual void SetScale(float x, float y, float z);
		///
		/// Set the scale of the entity with Vector3f.
		///
		virtual void SetScale(Vector3f scale);
		///
		/// Set the rotation of the entity with seperate floats.
		///
		virtual void SetRotation(float x, float y, float z);
		///
		/// Set the rotation of the entity with Vector3f.
		///
		virtual void SetRotation(Vector3f rotation);
		///
		/// Set the name of the asset the entity is supposed to use.
		///
		virtual void SetAssetName(const std::string &assetName);
		///
		/// Set what type of entity this entity is with EntityType.
		///
		virtual void SetEntityType(EntityType type);
		///
		/// Get the name of the asset the entity is using.
		///
		virtual std::string GetAssetName() const;
		///
		/// Get the EntityType of the entity.
		///
		virtual EntityType GetEntityType() const;
		///
		/// Get the current position of the entity.
		///
		virtual Vector3f GetPosition() const;
		///
		/// Get the current scale of the entity.
		///
		virtual Vector3f GetScale() const;
		///
		/// Get the current rotation of the entity.
		///
		virtual Vector3f GetRotation() const;
	protected:
		std::string m_assetName;
		EntityType m_entityType;
		Vector3f m_position;
		Vector3f m_scale;
		Vector3f m_rotation;
	};

}

#endif