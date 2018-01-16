#ifndef ABSTRACTTERRAIN_H
#define ABSTRACTTERRAIN_H

#include "std.h"
#include "Transform.h"

namespace se {

	class AbstractTerrain {
	public:
		virtual void Create(const std::string &heightMap, const std::string &texture) = 0;
		virtual void Process() = 0;
		virtual void Release() = 0;
	protected:
		Transform3f m_transform;
	};

}

#endif