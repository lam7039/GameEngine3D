#ifndef ENTITY_H
#define ENTITY_H

#include "std.h"
#include "Vector3.h"

namespace se {

	class Entity {
	public:
		Entity();
		void Init(const std::string &filename);
		void SetRotation(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		virtual void Update(float delta);
		virtual void Render();
		Vector3<float> GetPosition();
		Vector3<float> GetRotation();
		std::string GetFilename();
	protected:
		std::string m_filenameMesh;
		Vector3<float> m_position;
		Vector3<float> m_rotation;
	};

}

#endif