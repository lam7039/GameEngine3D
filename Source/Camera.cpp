#include "Camera.h"
#include <iostream>

namespace se {

	Camera::Camera() {
		m_transform.posZ = -20.0f;
		m_speed = 20.0f;
		m_rotateSpeed = 2.0f;
	}

	void Camera::Initialize(Input *input) {
		m_input = input;
	}

	void Camera::Update(float delta) {
		m_input->Update();
		if (m_input->IsPressed(DIK_W)) {
			m_transform.posZ += m_speed * delta;
		}
		if (m_input->IsPressed(DIK_A)) {
			m_transform.posX -= m_speed * delta;
		}
		if (m_input->IsPressed(DIK_S)) {
			m_transform.posZ -= m_speed * delta;
		}
		if (m_input->IsPressed(DIK_D)) {
			m_transform.posX += m_speed * delta;
		}
		if (m_input->IsPressed(DIK_UP)) {
			m_transform.posY += m_speed * delta;
		}
		if (m_input->IsPressed(DIK_DOWN)) {
			m_transform.posY -= m_speed * delta;
		}
		if (m_input->IsPressed(DIK_LEFT)) {
			m_transform.rotX -= m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_RIGHT)) {
			m_transform.rotX += m_rotateSpeed * delta;
		}

		//float pitchRadian = D3DXToRadian(m_transform.rotX);
		//float yawRadian = D3DXToRadian(m_transform.rotY);
		//m_transform.posX = m_speed * sinf(yawRadian) * cosf(pitchRadian);
		//m_transform.posZ = m_speed * cosf(yawRadian) * sinf(pitchRadian);

		m_position.x = m_transform.posX;
		m_position.y = m_transform.posY;
		m_position.z = m_transform.posZ;

		m_lookAt.x = 0.0f;
		m_lookAt.y = 0.0f;
		m_lookAt.z = 15.0f;

		m_up.x = 0.0f;
		m_up.y = 1.0f;
		m_up.z = 0.0f;

		D3DXMatrixRotationYawPitchRoll(&m_rotation, m_transform.rotX, 0.0f, 0.0f);
		D3DXVec3TransformCoord(&m_lookAt, &m_lookAt, &m_rotation);
		D3DXVec3TransformCoord(&m_up, &m_up, &m_rotation);

		m_lookAt = m_position + m_lookAt;

		//View (camera)
		D3DXMatrixLookAtLH(&m_matView, &m_position, &m_lookAt, &m_up);
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
