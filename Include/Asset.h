#ifndef ASSET_H
#define ASSET_H

#include "std.h"

namespace se {

	enum AssetType {
		UNKNOWN = 0,
		MESH = 1,
		TERRAIN = 2,
		SKYBOX = 3
	};

	enum State {
		Inactive = 0,
		Created = 1,
		Loaded = 2,
		Processed = 3,
		Destroyed = 4
	};

	class AbstractAsset {
	public:
		virtual void Create() = 0;
		virtual void Load() = 0;
		virtual void Process() = 0;
		virtual void Release() = 0;
		void SetPath(const std::string &path) {
			m_path = path;
		}
		std::string GetPath() {
			return m_path;
		}
	protected:
		std::string m_path;
		AssetType type = UNKNOWN;
	};

}

#endif