#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "std.h"
#include "Input.h"
#include "Camera.h"

namespace se {

	///
	/// Use this class to control the movement of your camera
	///
	class CameraController {
	public:

		CameraController(AbstractCamera *camera, Input *input);
		void HandleInput(float delta);
		///
		/// Set the position of the camera to the given target
		///
		void SetTarget(Transform3f *target);
		///
		/// Get the current target of the camera
		///
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