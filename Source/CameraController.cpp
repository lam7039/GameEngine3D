#include "CameraController.h"

namespace se {

	CameraController::CameraController(AbstractCamera *camera, Input *input) {
		m_camera = camera;
		m_input = input;
		m_pi = 3.141592;
	}

	void CameraController::HandleInput(float delta) {
		//TODO: customcontrols
		//if (m_customControl) {
		//	return;
		//}
		//Freeroaming camera
		Transform3f *transform = m_camera->GetTarget();
		if (m_input->IsPressed(DIK_W)) {
			transform->posY += m_speed * -sin(m_pitch) * delta;
			if (ToRadian(transform->rotX) < (m_pi / 2) && ToRadian(transform->rotX) > -(m_pi / 2)) {
				transform->posX += m_speed * cos(m_yaw) * delta;
				transform->posZ += m_speed * -sin(m_yaw) * delta;
			}
		}
		if (m_input->IsPressed(DIK_A)) {
			transform->posX += m_speed * cos(m_yaw - (m_pi / 2))  * delta;
			transform->posZ += m_speed * -sin(m_yaw - (m_pi / 2)) * delta;
		}
		if (m_input->IsPressed(DIK_S)) {
			transform->posY -= m_speed * -sin(m_pitch) * delta;
			if (ToRadian(transform->rotX) < (m_pi / 2) && ToRadian(transform->rotX) > -(m_pi / 2)) {
				transform->posX -= m_speed * cos(m_yaw) * delta;
				transform->posZ -= m_speed * -sin(m_yaw) * delta;
			}
		}
		if (m_input->IsPressed(DIK_D)) {
			transform->posX += m_speed * cos(m_yaw + (m_pi / 2))  * delta;
			transform->posZ += m_speed * -sin(m_yaw + (m_pi / 2)) * delta;
		}
		if (m_input->IsPressed(DIK_UP) && ToRadian(transform->rotX) > -(m_pi / 2)) {
			transform->rotX -= m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_DOWN) && ToRadian(transform->rotX) < m_pi / 2) {
			transform->rotX += m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_LEFT)) {
			transform->rotY -= m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_RIGHT)) {
			transform->rotY += m_rotateSpeed * delta;
		}
		if (m_input->IsPressed(DIK_E)) {
			transform->posY += m_speed  * delta;
		}
		if (m_input->IsPressed(DIK_C)) {
			transform->posY -= m_speed * delta;
		}

		m_camera->Update(delta);
	}

	float CameraController::ToRadian(float value) {
		return (value) * (3.141592 / 180.0f);
	}

}