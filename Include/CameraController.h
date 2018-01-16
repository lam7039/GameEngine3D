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
	private:
		AbstractCamera *m_camera;
		Input *m_input;
		float m_pi;
		float ToRadian(float value);
	};

}

#endif