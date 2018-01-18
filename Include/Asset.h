#ifndef ASSET_H
#define ASSET_H

#include "std.h"

namespace se {

	///
	/// With this interface you can create you own Asset type to load in the AssetManager
	///
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