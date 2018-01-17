#ifndef SKYBOX_H
#define SKYBOX_H

#include "Transform.h"
#include "Entity.h"

namespace se {

	class AbstractSkybox : public Entity {
	public:
		virtual void Create(Transform3f transform, const std::string &src) = 0;
		virtual void Process() = 0;
		virtual void Release() = 0;

	};

}

#endif