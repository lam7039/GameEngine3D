#ifndef ENTITY_H
#define ENTITY_H

#include "std.h"
#include "Transform.h"

namespace se {

	class Entity {
	public:
		Entity();
		void Init(const std::string &filename);
		void SetScale(float scale);
		void SetRotation(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		virtual void Update(float delta);
		virtual void Render();
		Transform3f GetTarget() const;
		std::string GetFilename() const;
	protected:
		std::string m_filenameMesh;
		Transform3f m_transform;
	};

}

#endif