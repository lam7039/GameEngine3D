#ifndef ASSET_H
#define ASSET_H

#include "std.h"

namespace se {

	class AbstractAsset {
	public:
		virtual void Create() = 0;
		virtual void Load() = 0;
		virtual void Process() = 0;
		virtual void Release() = 0;
	protected:
		std::string m_path;
	};
}

#endif