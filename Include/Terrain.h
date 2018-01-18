#ifndef ABSTRACTTERRAIN_H
#define ABSTRACTTERRAIN_H

#include "std.h"
#include "Entity.h"

namespace se {

	///
	/// With this interface you can create your own terrain to load into a Scene
	///
	class AbstractTerrain : public Entity {
	public:
		virtual void Create(const std::string &heightMap, const std::string &texture) = 0;
		virtual void Process() = 0;
		virtual void Release() = 0;
	};

}

#endif