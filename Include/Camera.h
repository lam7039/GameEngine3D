#ifndef CAMERA_H
#define CAMERA_H

#include "std.h"
#include "Entity.h"

namespace se {

	//Shouldn't be an entity, has a meshFileName f.ex like this
	class Camera : public Entity {
	public:
		Camera();
	};

}

#endif