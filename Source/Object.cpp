#include "Object.h"
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

Object::Object() {
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_rotZ = 0.0f;
}

void Object::Init(const std::string &filename) {
	m_filename = filename;
	m_mesh = &AssetLoader::GetInstance()->GetMeshes()->at(m_filename);
}

void Object::Update(float delta) {

}

void Object::Render(LPDIRECT3DDEVICE9 device) {
	D3DXMatrixRotationYawPitchRoll(&m_matRotate, m_rotX, m_rotY, m_rotZ);
	D3DXMatrixTranslation(&m_matTranslate, m_posX, m_posY, m_posZ);
	device->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
	m_mesh->Render();
}

void Object::SetPosition(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

void Object::SetRotation(float x, float y, float z) {
	m_rotX = x;
	m_rotY = y;
	m_rotZ = z;
}

SE_END_NAMESPACE