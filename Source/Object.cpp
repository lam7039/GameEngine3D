#include <d3dx9.h>
#include "Object.h"
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

Object::Object() {
	m_filename = "";
}

void Object::Init(/*const std::string &objectName, */const std::string &filename) {
	m_filename = filename;
	m_mesh = &AssetLoader::GetInstance()->GetMeshes()->at(m_filename);
}

void Object::Update(float delta) {
	unsigned int iTime = (int)delta / 10 % 1000;
	SetRotation(iTime * (2.0f * D3DX_PI) / 1000.0f, 0.0f, 0.0f);
}

//TODO: put this in direct3d.cpp somehow
void Object::Render() {
	D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_rotX, m_rotY, m_rotZ);
	D3DXMatrixTranslation(&m_matTranslate, m_posX, m_posY, m_posZ);
	m_mesh->m_device->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
	m_mesh->Render();
}

void Object::SetRotation(float x, float y, float z) {
	//m_rotation.Set(x, y, z);
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;
}

void Object::SetPosition(float x, float y, float z) {
	//m_position.Set(x, y, z);
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

std::string Object::GetFilename() {
	return m_filename;
}

SE_END_NAMESPACE