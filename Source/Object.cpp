#include "Object.h"

SE_BEGIN_NAMESPACE

Object::Object(const std::string &meshLocation) {
	m_posX = 0.0f;
	m_posY = 0.0f;
	m_posZ = 0.0f;
}

void Object::Update(LPDIRECT3DDEVICE9 device) {
	D3DXMATRIX matRotate;
	D3DXMATRIX matTranslate;
	D3DXMatrixRotationY(&matRotate, (2.0f * D3DX_PI) / 1000.0f);
	D3DXMatrixTranslation(&matTranslate, 0.0f, 0.0f, 0.0f);
	device->SetTransform(D3DTS_WORLD, &(matRotate * matTranslate));
}

void Object::Render() {
	m_mesh.Render();
}

void Object::ChangePosition(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

SE_END_NAMESPACE