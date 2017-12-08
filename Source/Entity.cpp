#include "Entity.h"
#include "AssetLoader.h"

namespace se {

	Entity::Entity() {
		m_filenameMesh = "";
	}

	void Entity::Init(const std::string &filenameMesh) {
		m_filenameMesh = filenameMesh;
	}

	void Entity::Update(float delta) {
	}

	void Entity::Render() {
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

	Vector3<float> Entity::GetPosition() {
		return m_position;
	}

	Vector3<float> Entity::GetRotation() {
		return m_rotation;
	}

	std::string Entity::GetFilename() {
		return m_filenameMesh;
	}

}
