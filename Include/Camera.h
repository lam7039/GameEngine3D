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
		void Initialize(Input *input);
		void Update(float delta);
		Transform3f GetTarget() const;
	private:
		Input *m_input;
		Transform3f m_transform;
		float m_speed;
		float m_rotateSpeed;
		float m_pitch;
		float m_yaw;
		void HandleInput(float delta);
	};

}

#endif