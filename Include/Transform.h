#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "std.h"

namespace se {

	///
	/// For all your transformation needs
	///
	class Transform3f {
	public:
		float posX;
		float posY;
		float posZ;
		float rotX;
		float rotY;
		float rotZ;
		float scaleX;
		float scaleY;
		float scaleZ;

		Transform3f() {
			posX = 0.0f;
			posY = 0.0f;
			posZ = 0.0f;
			rotX = 0.0f;
			rotY = 0.0f;
			rotZ = 0.0f;
			scaleX = 1.0f;
			scaleY = 1.0f;
			scaleZ = 1.0f;
		}
	};

}

#endif