#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "std.h"
#include "Input.h"
#include "Camera.h"

namespace se {

	class CameraController {
	public:
		CameraController(AbstractCamera *camera, Input *input);
		void HandleInput(float delta);
		void SetTarget(Transform3f *target);
		Transform3f *GetTarget() const;
	private:
		AbstractCamera *m_camera;
		Input *m_input;
		float m_pi;
		float ToRadian(float value);
		Transform3f *m_target;
	};

}

#endif