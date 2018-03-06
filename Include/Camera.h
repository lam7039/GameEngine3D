#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "Renderer.h"
#include "Input.h"

namespace se {

	class Camera : public Entity {
	public:
		Camera(AbstractRenderer *renderer, AbstractInput *input, const std::string &assetName);
		void Update(float delta) override;
		void Render();
		///
		/// Set the position of the camera
		///
		void SetTarget(Vector3f *position, Vector3f *rotation);
		///
		/// Get the current position of the camera
		///
		Vector3f *GetPosition();
	private:
		AbstractRenderer *m_renderer;
		AbstractInput *m_input;
		Vector3f *m_targetPosition;
		Vector3f *m_targetRotation;
		float m_pi;
		float m_speed;
		float m_rotateSpeed;
		float m_pitch;
		float m_yaw;
		float ToRadian(float value);
	};

}

#endif