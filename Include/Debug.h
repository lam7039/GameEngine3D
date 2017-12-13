#ifndef DEBUG_H
#define DEBUG_H

#include "std.h"
#include <fstream>

namespace se {

	class Debug {
	public:
		Debug(const std::string &filename);
		~Debug();
		void Log(int id, const std::string &file, int line, const std::string &source);
	private:
		std::ofstream m_file;
		std::string m_path;
	};

}

#endif
