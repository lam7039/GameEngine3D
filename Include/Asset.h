#ifndef ASSET_H
#define ASSET_H

#include "std.h"

namespace se {
	//TODO: implement state
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
			m_path = "Assets\\" + path;
		}
		std::string GetPath() const {
			return m_path;
		}
	protected:
		std::string m_path;
	};

}

#endif