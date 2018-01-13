#ifndef ENTITY_H
#define ENTITY_H

#include "std.h"
#include "Transform.h"

namespace se {

	class Entity {
	public:
		Entity();
		void SetScale(float scale);
		void SetRotation(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		virtual void Update(float delta);
		Transform3f GetTarget() const;
		std::string GetEntityName() const;
	protected:
		std::string m_entityName;
		Transform3f m_transform;
	};

}

#endif