#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "std.h"
#include "Input.h"
#include "Camera.h"

namespace se {

	class CameraController {
	public:
		CameraController(Input *input);
		void HandleInput(float delta);
	private:
		Input *m_input;
		Camera m_camera;
	};

}

#endif