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

		D3DXMATRIX m_matView;
		D3DXMATRIX m_rotation;
		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_lookAt;
		D3DXVECTOR3 m_up;
	};

}

#endif