#ifndef CAMERA_H
#define CAMERA_H

#include "std.h"
#include "Input.h"
#include "Transform.h"
#include "DirectX9\Direct3D.h"

namespace se {

	class Camera {
	public:
		Camera();
		void HandleInput(Input *input, float delta);
		void Update();
		Transform3f GetTarget() const;
	private:
		Transform3f m_transform;
		float m_speed;
		float m_rotateSpeed;
		float m_pitch;
		float m_yaw;
	};

}

#endif