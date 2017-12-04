//TODO: d3dx9.h is being detected in executable project
//#include <d3dx9.h>
#include "Object.h"
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

Object::Object() {
	m_filename = "";
}

void Object::Init(/*const std::string &objectName, */const std::string &filename) {
	m_filename = filename;
	//m_mesh = &AssetLoader::GetInstance()->GetMeshes()->at(m_filename);
}

void Object::Update(float delta) {
	unsigned int iTime = (int)delta / 10 % 1000;
	SetRotation(iTime * (2.0f * D3DX_PI) / 1000.0f, 0.0f, 0.0f);
}

void Object::Render() {
//	D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_rotation.X, m_rotation.Y, m_rotation.Z);
//	D3DXMatrixTranslation(&m_matTranslate, m_position.X, m_position.Y, m_position.Z);
//	m_mesh->m_device->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
//	m_mesh->Render();
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
	return m_filename;
}

SE_END_NAMESPACE