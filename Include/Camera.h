#ifndef CAMERA_H
#define CAMERA_H

#include "std.h"
#include "Input.h"
#include "Vector3.h"

namespace se {

	//Shouldn't be an entity, has a meshFileName f.ex like this
	class Camera {
	public:
		Camera();
		void Initialize(Input *input);
		void Update(float delta);
		Vector3<float> GetPosition();
		Vector3<float> GetRotation();
	private:
		Input *m_input;
		Vector3<float> m_position;
		Vector3<float> m_rotation;
		float m_speed;
	};

}

#endif