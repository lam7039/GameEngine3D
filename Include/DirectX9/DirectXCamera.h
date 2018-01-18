#ifndef DIRECTXCAMERA_H
#define DIRECTXCAMERA_H

#include "std.h"
#include "Camera.h"
#include "Input.h"
#include "DirectX9\Direct3D.h"

namespace se {

	///
	/// The camera for DirectX 9
	///
	class DirectXCamera : public AbstractCamera {
	public:
		DirectXCamera(LPDIRECT3DDEVICE9 device, int screenWidth, int screenHeight);
		void Update(float delta) override;
	private:
		LPDIRECT3DDEVICE9 m_device;
		int m_screenWidth;
		int m_screenHeight;
	};

}

#endif