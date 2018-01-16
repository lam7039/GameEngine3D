#ifndef SKYBOX_H
#define SKYBOX_H

namespace se {

	class AbstractSkybox {
	public:
		virtual void Create(const std::string &topSrc, const std::string &bottomSrc, const std::string &leftSrc, const std::string &rightSrc) = 0;
		virtual void Process() = 0;
		virtual void Release() = 0;
	};

}

#endif