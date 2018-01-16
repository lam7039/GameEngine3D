#include "Camera.h"

namespace se {

	float AbstractCamera::GetSpeed() const {
		return m_speed;
	}
	float AbstractCamera::GetRotationSpeed() const {
		return m_rotateSpeed;
	}
	float AbstractCamera::GetPitch() const {
		return m_pitch;
	}
	float AbstractCamera::GetYaw() const {
		return m_yaw;
	}

}