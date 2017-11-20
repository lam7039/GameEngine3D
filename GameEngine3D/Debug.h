#ifndef DEBUG_H
#define DEBUG_H

#include "std.h"

SE_BEGIN_NAMESPACE

class Debug {
public:
	Debug();
	void WriteFile(const std::string& source);
	void AppendFile(const std::string& source);
private:
	std::string m_path;
};

SE_END_NAMESPACE

#endif
