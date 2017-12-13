#include <fstream>
#include <string> 
#include "stdafx.h"

class Log {
public:
	Log(const std::string &filename);
	~Log();

	void Write(const int &id, const std::string &file, const std::string &line, const std::string &msg);
private:
	std::ofstream m_stream;
};