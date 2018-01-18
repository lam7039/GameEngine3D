#include "DirectX9/DirectXCamera.h"

namespace se {

	DirectXCamera::DirectXCamera(LPDIRECT3DDEVICE9 device, int screenWidth, int screenHeight) {
		m_device = device;
		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;
		m_speed = 50.0f;
		m_rotateSpeed = 70.0f;
		m_transform.posZ = -15.0f;
	}

	void DirectXCamera::Update(float delta) {
		m_pitch = D3DXToRadian(m_transform.rotX);
		m_yaw = D3DXToRadian(m_transform.rotY) - (D3DX_PI / 2);

		D3DXVECTOR3 position;
		position.x = m_transform.posX;
		position.y = m_transform.posY;
		position.z = m_transform.posZ;

		D3DXVECTOR3 lookAt;
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 15.0f;

		D3DXVECTOR3 up;
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		D3DXMATRIX rotation;
		D3DXMatrixRotationYawPitchRoll(&rotation, m_yaw + (D3DX_PI / 2), m_pitch, 0.0f);
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotation);
		D3DXVec3TransformCoord(&up, &up, &rotation);

		lookAt = position + lookAt;

		//View
		D3DXMATRIX m_matView;
		D3DXMatrixLookAtLH(&m_matView, &position, &lookAt, &up);
		m_device->SetTransform(D3DTS_VIEW, &m_matView);

		//Projection
		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, m_screenWidth / m_screenHeight, 1.0f, 1000.0f);
		m_device->SetTransform(D3DTS_PROJECTION, &matProj);
	}

}