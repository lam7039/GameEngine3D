#include "Object.h"
#include "AssetLoader.h"

SE_BEGIN_NAMESPACE

Object::Object() {
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
}

void Object::Init(const std::string &filename) {
	m_filename = filename;
	m_mesh = &AssetLoader::GetInstance()->GetMeshes()->at(m_filename);
}

void Object::Update(LPDIRECT3DDEVICE9 device) {
	D3DXMATRIX m_matRotate;
	D3DXMatrixIdentity(&m_matRotate);
	D3DXMatrixRotationY(&m_matRotate, (D3DX_PI / 4 * 3));
	D3DXMATRIX m_matTranslate;
	D3DXMatrixIdentity(&m_matTranslate);
	D3DXMatrixTranslation(&m_matTranslate, m_posX, m_posY, m_posZ);
	device->SetTransform(D3DTS_WORLD, &(m_matRotate * m_matTranslate));
}

void Object::Render() {
	m_mesh->Render();
}

void Object::ChangePosition(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

SE_END_NAMESPACE