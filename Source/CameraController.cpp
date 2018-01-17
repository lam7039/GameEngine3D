#include "CameraController.h"

namespace se {

	CameraController::CameraController(AbstractCamera *camera, Input *input) {
		m_camera = camera;
		m_input = input;
		m_pi = 3.141592;
		m_target = nullptr;
	}

	void CameraController::HandleInput(float delta) {
		if (!m_target) {
			//Freeroaming camera
			Transform3f *transform = m_camera->GetTarget();
			if (m_input->IsPressed(DIK_W)) {
				transform->posY += m_camera->GetSpeed() * -sin(m_camera->GetPitch()) * delta;
				if (ToRadian(transform->rotX) < (m_pi / 2) && ToRadian(transform->rotX) > -(m_pi / 2)) {
					transform->posX += m_camera->GetSpeed() * cos(m_camera->GetYaw()) * delta;
					transform->posZ += m_camera->GetSpeed() * -sin(m_camera->GetYaw()) * delta;
				}
			}
			if (m_input->IsPressed(DIK_A)) {
				transform->posX += m_camera->GetSpeed() * cos(m_camera->GetYaw() - (m_pi / 2))  * delta;
				transform->posZ += m_camera->GetSpeed() * -sin(m_camera->GetYaw() - (m_pi / 2)) * delta;
			}
			if (m_input->IsPressed(DIK_S)) {
				transform->posY -= m_camera->GetSpeed() * -sin(m_camera->GetPitch()) * delta;
				if (ToRadian(transform->rotX) < (m_pi / 2) && ToRadian(transform->rotX) > -(m_pi / 2)) {
					transform->posX -= m_camera->GetSpeed() * cos(m_camera->GetYaw()) * delta;
					transform->posZ -= m_camera->GetSpeed() * -sin(m_camera->GetYaw()) * delta;
				}
			}
			if (m_input->IsPressed(DIK_D)) {
				transform->posX += m_camera->GetSpeed() * cos(m_camera->GetYaw() + (m_pi / 2))  * delta;
				transform->posZ += m_camera->GetSpeed() * -sin(m_camera->GetYaw() + (m_pi / 2)) * delta;
			}
			if (m_input->IsPressed(DIK_UP) && ToRadian(transform->rotX) > -(m_pi / 2)) {
				transform->rotX -= m_camera->GetRotationSpeed() * delta;
			}
			if (m_input->IsPressed(DIK_DOWN) && ToRadian(transform->rotX) < m_pi / 2) {
				transform->rotX += m_camera->GetRotationSpeed() * delta;
			}
			if (m_input->IsPressed(DIK_LEFT)) {
				transform->rotY -= m_camera->GetRotationSpeed() * delta;
			}
			if (m_input->IsPressed(DIK_RIGHT)) {
				transform->rotY += m_camera->GetRotationSpeed() * delta;
			}
			if (m_input->IsPressed(DIK_E)) {
				transform->posY += m_camera->GetSpeed()  * delta;
			}
			if (m_input->IsPressed(DIK_C)) {
				transform->posY -= m_camera->GetSpeed() * delta;
			}

		}
		else {
			
			m_camera->SetPosition(m_target->posX, m_target->posY, m_target->posZ);
			m_camera->SetRotation(m_target->rotX, m_target->rotY, m_target->rotZ);
		}
		m_camera->Update(delta);
	}

	void CameraController::SetTarget(Transform3f *target) {
		m_target = target;
	}

	Transform3f *CameraController::GetTarget() const {
		if (m_target) {
			return m_target;
		}
		return m_camera->GetTarget();
	}
	float CameraController::ToRadian(float value) {
		return (value) * (m_pi / 180.0f);
	}

}