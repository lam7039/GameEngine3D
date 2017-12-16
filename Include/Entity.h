#ifndef ENTITY_H
#define ENTITY_H

#include "std.h"
#include "Vector3.h"

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
		float GetScale();
		Vector3<float> GetRotation();
		Vector3<float> GetPosition();
		std::string GetFilename();
	protected:
		std::string m_filenameMesh;
		float m_scale;
		Vector3<float> m_rotation;
		Vector3<float> m_position;
	};

}

#endif