#ifndef DEBUG_H
#define DEBUG_H

#include "std.h"

BEGIN_NAMESPACE

class Debug {
public:
	Debug();
	void WriteFile(const std::string &source);
	void AppendFile(const std::string &source);
private:
	std::string m_path;
};

END_NAMESPACE

#endif
