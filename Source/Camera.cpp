#include "Camera.h"

namespace se {

	Camera::Camera(AbstractRenderer *renderer, AbstractInput *input, const std::string &assetName) {
		m_renderer = renderer;
		m_input = input;
		m_pi = 3.141592;
		m_targetPosition = nullptr;
		m_targetRotation = nullptr;
		m_speed = 50.0f;
		m_rotateSpeed = 70.0f;
		m_position.z = -15.0f;
		m_assetName = assetName;
		m_yaw = m_renderer->GetViewAxes().x;
		m_pitch = m_renderer->GetViewAxes().y;
	}

	void Camera::Update(float delta) {
		if (!m_targetPosition && !m_targetRotation) {
			m_yaw = m_renderer->GetViewAxes().x;
			m_pitch = m_renderer->GetViewAxes().y;
			// Freeroaming camera.
			if (m_input->IsPressed(SE_KEY_W)) {
				m_position.y += m_speed * -sin(m_pitch) * delta;
				if (ToRadian(m_rotation.x) < (m_pi / 2) && ToRadian(m_rotation.x) > -(m_pi / 2)) {
					m_position.x += m_speed * cos(m_yaw) * delta;
					m_position.z += m_speed * -sin(m_yaw) * delta;
				}
			}
			if (m_input->IsPressed(SE_KEY_A)) {
				m_position.x += m_speed * cos(m_yaw - (m_pi / 2))  * delta;
				m_position.z += m_speed * -sin(m_yaw - (m_pi / 2)) * delta;
			}
			if (m_input->IsPressed(SE_KEY_S)) {
				m_position.y -= m_speed * -sin(m_pitch) * delta;
				if (ToRadian(m_rotation.x) < (m_pi / 2) && ToRadian(m_rotation.x) > -(m_pi / 2)) {
					m_position.x -= m_speed * cos(m_yaw) * delta;
					m_position.z -= m_speed * -sin(m_yaw) * delta;
				}
			}
			if (m_input->IsPressed(SE_KEY_D)) {
				m_position.x += m_speed * cos(m_yaw + (m_pi / 2))  * delta;
				m_position.z += m_speed * -sin(m_yaw + (m_pi / 2)) * delta;
			}
			if (m_input->IsPressed(SE_KEY_UP) && ToRadian(m_rotation.x) > -(m_pi / 2)) {
				m_rotation.x -= m_rotateSpeed * delta;
			}
			if (m_input->IsPressed(SE_KEY_DOWN) && ToRadian(m_rotation.x) < m_pi / 2) {
				m_rotation.x += m_rotateSpeed * delta;
			}
			if (m_input->IsPressed(SE_KEY_LEFT)) {
				m_rotation.y -= m_rotateSpeed * delta;
			}
			if (m_input->IsPressed(SE_KEY_RIGHT)) {
				m_rotation.y += m_rotateSpeed * delta;
			}
			if (m_input->IsPressed(SE_KEY_E)) {
				m_position.y += m_speed  * delta;
			}
			if (m_input->IsPressed(SE_KEY_C)) {
				m_position.y -= m_speed * delta;
			}
			m_renderer->SetViewTransform(m_position, m_rotation);
		}
		else {
			SetPosition(m_targetPosition->x, m_targetPosition->y, m_targetPosition->z);
			SetRotation(m_targetRotation->x, m_targetRotation->y, m_targetRotation->z);
		}
	}

	void Camera::Render() {
		m_renderer->Render(m_assetName);
	}

	void Camera::SetTarget(Vector3f *position, Vector3f *rotation) {
		m_targetPosition = position;
		m_targetRotation = rotation;
	}

	Vector3f *Camera::GetPosition() {
		if (m_targetPosition) {
			return m_targetPosition;
		}
		return &m_position;
	}

	float Camera::ToRadian(float value) {
		return (value) * (m_pi / 180.0f);
	}

}