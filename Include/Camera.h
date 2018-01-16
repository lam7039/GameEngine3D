#ifndef CAMERA_H
#define CAMERA_H

#include "std.h"
#include "Entity.h"
#include "Input.h"
//TODO: fix camera abstraction
#include "DirectX9\Direct3D.h"

namespace se {

	class Camera : Entity {
	public:
		Camera();
		void HandleInput(Input *input, float delta);
		void Update(float delta) override;
	private:
		float m_speed;
		float m_rotateSpeed;
		float m_pitch;
		float m_yaw;
	};

}

#endif