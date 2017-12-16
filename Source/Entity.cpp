#include "Entity.h"

namespace se {

	Entity::Entity() {
		m_filenameMesh = "";
		m_scale = 1.0f;
		m_rotation = { 0.0f, 0.0f, 0.0f };
		m_position = { 0.0f, 0.0f, 0.0f };
	}

	void Entity::Init(const std::string &filenameMesh) {
		m_filenameMesh = filenameMesh;
	}

	void Entity::Update(float delta) {
	}

	void Entity::Render() {
	}

	void Entity::SetScale(float scale) {
		m_scale = scale;
	}

	void Entity::SetRotation(float x, float y, float z) {
		m_rotation.Set(x, y, z);
		//m_rotX = x;
		//m_rotY = y;
		//m_rotZ = z;
	}

	void Entity::SetPosition(float x, float y, float z) {
		m_position.Set(x, y, z);
		//m_posX = x;
		//m_posY = y;
		//m_posZ = z;
	}

	float Entity::GetScale() {
		return m_scale;
	}

	Vector3<float> Entity::GetRotation() {
		return m_rotation;
	}

	Vector3<float> Entity::GetPosition() {
		return m_position;
	}

	std::string Entity::GetFilename() {
		return m_filenameMesh;
	}

}
