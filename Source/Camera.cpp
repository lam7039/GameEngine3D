#include "Camera.h"

namespace se {

	Camera::Camera() {
		m_position.Set(0.0f, 5.0f, 0.0f);
		m_rotation.Set(0.0f, 0.0f, 0.0f);
		m_speed = 20.0f;
	}

	void Camera::Initialize(Input *input) {
		m_input = input;
	}

	void Camera::Update(float delta) {
		m_input->Update();
		if (m_input->IsPressed(DIK_W)) {
			m_position.Z += m_speed * delta;
		}
		if (m_input->IsPressed(DIK_A)) {
			m_position.X -= m_speed * delta;
		}
		if (m_input->IsPressed(DIK_S)) {
			m_position.Z -= m_speed * delta;
		}
		if (m_input->IsPressed(DIK_D)) {
			m_position.X += m_speed * delta;
		}
		if (m_input->IsPressed(DIK_UP)) {
			m_position.Y += m_speed * delta;
		}
		if (m_input->IsPressed(DIK_DOWN)) {
			m_position.Y -= m_speed * delta;
		}
	}

	Vector3<float> Camera::GetPosition() {
		return m_position;
	}
	
	Vector3<float> Camera::GetRotation() {
		return m_rotation;
	}

}
