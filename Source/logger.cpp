#include "stdafx.h"
#include "logger.h"

Log::Log(const std::string &filename)
{
	m_stream.open(filename);
}

Log::~Log()
{
	m_stream.close();
}

void Log::Write(const int &id, const std::string &file, const std::string &line, const std::string &msg)
{
	//check if info/warning/error
	switch (id) {
	case 0:
		m_stream << __DATE__ << " " << __TIME__ << " " << file << " " << line << " [INFO] " + msg << std::endl;
		break;
	case 1:
		m_stream << __DATE__ << " " << __TIME__ << " " << file << " " << line << " [WARNING] " + msg << std::endl;
		break;
	case 2:
		m_stream << __DATE__ << " " << __TIME__ << " " << file << " " << line << " [ERROR] " + msg << std::endl;
		break;
	}
}