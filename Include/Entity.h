#ifndef ENTITY_H
#define ENTITY_H

#include "std.h"
#include "Transform.h"

namespace se {

	class Entity {
	public:
		Entity();
		void SetScale(float x, float y, float z);
		void SetRotation(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		virtual void Update(float delta);
		std::string GetEntityName() const;
		std::string GetAssetName() const;
		Transform3f *GetTarget();
	protected:
		std::string m_entityName;
		std::string m_assetName;
		Transform3f m_transform;
	};

}

#endif