#include "Object.h"
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

Object::Object() {
	m_filenameMesh = "";
}

void Object::Init(const std::string &filenameMesh) {
	m_filenameMesh = filenameMesh;
}

void Object::Update(float delta) {
}

void Object::Render() {
}

void Object::SetRotation(float x, float y, float z) {
	m_rotation.Set(x, y, z);
	//m_rotX = x;
	//m_rotY = y;
	//m_rotZ = z;
}

void Object::SetPosition(float x, float y, float z) {
	m_position.Set(x, y, z);
	//m_posX = x;
	//m_posY = y;
	//m_posZ = z;
}

Vector3<float> Object::GetPosition() {
	return m_position;
}

Vector3<float> Object::GetRotation() {
	return m_rotation;
}

std::string Object::GetFilename() {
	return m_filenameMesh;
}

SE_END_NAMESPACE