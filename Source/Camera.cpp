#include "Camera.h"
#include <iostream>

namespace se {

	Camera::Camera() {
		m_direction = 0.0f;
		m_speed = 10.0f;
		m_rotateSpeed = 50.0f;
	}

	void Camera::Initialize(Input *input) {
		m_input = input;
	}

	void Camera::Update(float delta) {
		m_input->Update();

		//float newX = cos(yawRadian) - sin(pitchRadian);
		//float newY = cos(yawRadian);
		//float newZ = cos(yawRadian) + sin(pitchRadian);
		//x = adjacent = direction * cos
		//z = opposite = direction * sin

		//D3DXVECTOR3 position;
		//D3DXVECTOR3 lookAt;
		//D3DXVECTOR3 forward;
		//D3DXVECTOR3 up;

		//forward = lookAt - position;
		//D3DXVec3Normalize(&forward, &forward);

		//if (m_input->IsPressed(DIK_W)) {
		//	position += forward * m_speed;
		//	lookAt += forward * m_speed;
		//}
		//if (m_input->IsPressed(DIK_S)) {
		//	position -= forward * m_speed;
		//	lookAt -= forward * m_speed;
		//}
		//if (m_input->IsPressed(DIK_A)) {
		//	D3DXVECTOR3 left;
		//	D3DXVec3Cross(&left, &up, &forward);
		//	position += left * m_speed;
		//}
		//if (m_input->IsPressed(DIK_D)) {
		//	D3DXVECTOR3 right;
		//	D3DXVec3Cross(&right, &forward, &up);
		//}

		float pitchRadian = D3DXToRadian(m_transform.rotX);
		float yawRadian = D3DXToRadian(m_transform.rotY);

		if (m_input->IsPressed(DIK_W)) {
			m_transform.posX += m_speed * cos(yawRadian) * delta;
			m_transform.posZ += m_speed * -sin(yawRadian) * delta;
		}
		if (m_input->IsPressed(DIK_S)) {	
			m_transform.posX -= m_speed * cos(yawRadian) * delta;
			m_transform.posZ -= m_speed * -sin(yawRadian) * delta;
		}
		if (m_input->IsPressed(DIK_A)) {
			m_transform.rotY -= m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_D)) {
			m_transform.rotY += m_rotateSpeed * delta;
		}

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
		D3DXMatrixRotationYawPitchRoll(&rotation, yawRadian + (D3DX_PI / 2), 0.0f, 0.0f);
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotation);
		D3DXVec3TransformCoord(&up, &up, &rotation);

		lookAt = position + lookAt;

		//View (camera)
		D3DXMATRIX m_matView;
		D3DXMatrixLookAtLH(&m_matView, &position, &lookAt, &up);
		Direct3D::GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

		//Projection
		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 800 / 500, 1.0f, 100.0f);
		Direct3D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	}

	Transform3f Camera::GetTarget() const {
		return m_transform;
	}

}
