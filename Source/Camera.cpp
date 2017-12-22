#include "Camera.h"
#include <iostream>

namespace se {

	Camera::Camera() {
		m_speed = 50.0f;
		m_rotateSpeed = 70.0f;
		m_transform.posZ = -15.0f;
	}

	void Camera::Initialize(Input *input) {
		m_input = input;
	}

	void Camera::Update(float delta) {
		HandleInput(delta);

		m_pitch = D3DXToRadian(m_transform.rotX);
		m_yaw = D3DXToRadian(m_transform.rotY) - (D3DX_PI / 2);

		D3DXVECTOR3 position;
		position.x = m_transform.posX;
		position.y = m_transform.posY;
		position.z = m_transform.posZ;

		std::cout << "x: " << position.x << " z: " << position.z << std::endl;

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
		Direct3D::GetDevice()->SetTransform(D3DTS_VIEW, &m_matView);

		//Projection
		D3DXMATRIX matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 800 / 500, 1.0f, 100.0f);
		Direct3D::GetDevice()->SetTransform(D3DTS_PROJECTION, &matProj);
	}

	void Camera::HandleInput(float delta) {
		m_input->Update();

		if (m_input->IsPressed(DIK_W)) {
			m_transform.posX += m_speed * cos(m_yaw) * delta;
			m_transform.posZ += m_speed * -sin(m_yaw) * delta;
		}
		if (m_input->IsPressed(DIK_A)) {
			m_transform.posX += m_speed * cos(m_yaw - (D3DX_PI / 2))  * delta;
			m_transform.posZ += m_speed * -sin(m_yaw - (D3DX_PI / 2)) * delta;
		}
		if (m_input->IsPressed(DIK_S)) {
			m_transform.posX -= m_speed * cos(m_yaw) * delta;
			m_transform.posZ -= m_speed * -sin(m_yaw) * delta;
		}
		if (m_input->IsPressed(DIK_D)) {
			m_transform.posX += m_speed * cos(m_yaw + (D3DX_PI / 2))  * delta;
			m_transform.posZ += m_speed * -sin(m_yaw + (D3DX_PI / 2)) * delta;
		}
		if (m_input->IsPressed(DIK_UP)) {
			m_transform.rotX -= m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_DOWN)) {
			m_transform.rotX += m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_LEFT)) {
			m_transform.rotY -= m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_RIGHT)) {
			m_transform.rotY += m_rotateSpeed * delta;
		}
	}

	Transform3f Camera::GetTarget() const {
		return m_transform;
	}

}
