#ifndef CAMERA_H
#define CAMERA_H

#include "std.h"
#include "Entity.h"

namespace se {

	class AbstractCamera : public Entity {
	protected:
		float m_speed;
		float m_rotateSpeed;
		float m_pitch;
		float m_yaw;
	};

}

#endif