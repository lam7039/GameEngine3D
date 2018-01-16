#ifndef DIRECTXCAMERA_H
#define DIRECTXCAMERA_H

#include "std.h"
#include "Camera.h"
#include "Input.h"

namespace se {

	class DirectXCamera : public AbstractCamera {
	public:
		DirectXCamera();
		void Update(float delta) override;
	};

}

#endif