#ifndef DIRECTXCAMERA_H
#define DIRECTXCAMERA_H

#include "std.h"
#include "Camera.h"
#include "Input.h"

namespace se {

	///
	/// The camera for DirectX 9
	///
	class DirectXCamera : public AbstractCamera {
	public:
		DirectXCamera(int screenWidth, int screenHeight);
		void Update(float delta) override;
	private:
		int m_screenWidth;
		int m_screenHeight;
	};

}

#endif