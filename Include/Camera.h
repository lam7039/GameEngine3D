#ifndef CAMERA_H
#define CAMERA_H

#include "Entity.h"
#include "Renderer.h"
#include "Input.h"

namespace se {

	///
	/// A default created camera Entity.
	///
	class Camera : public Entity {
	public:
		///
		/// Create a camera with a renderer and the input you want to use.
		///
		Camera(AbstractRenderer *renderer, AbstractInput *input, const std::string &assetName);
		///
		/// Set the position of the camera.
		///
		void SetTarget(Vector3f *position, Vector3f *rotation);
		///
		/// Updates camera logic, it defaults to logic for a freeroaming camera, if a target is set it'll update it to the target.
		///
		void Update(float delta) override;
		///
		/// Render the camera with the asset it is set to, if it's set to anything.
		///
		void Render(AbstractRenderer *renderer) override;
		///
		/// Get the current position of the camera.
		///
		Vector3f GetPosition() const override;
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