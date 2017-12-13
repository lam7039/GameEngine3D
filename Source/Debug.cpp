#include "Debug.h"

namespace se {

	Debug::Debug(const std::string &filename) {
		m_path = filename;
		//TODO: this doesn't reset the created logfile on start, idk, maybe it should be like this or at least be an option
		if (!m_file.is_open()) {
			m_file.open(m_path, std::ios::out);
		}
		if (m_file.is_open()) {
			m_file.close();
		}
	}

	void Debug::Log(int id, const std::string &file, int line, const std::string &source) {
		if (!m_file.is_open()) {
			m_file.open(m_path, std::ios::app);
		}
		m_file << __DATE__ << " " << __TIME__ << " " << file << " " << line;
		switch (id) {
		case 0:
			m_file << " [INFO] ";
			break;
		case 1:
			m_file << " [WARNING] ";
			break;
		case 2:
			m_file << " [ERROR] ";
			break;
		}
		m_file << source << std::endl;
		m_file.close();
	}

	Debug::~Debug() {
		if (m_file.is_open()) {
			m_file.close();
		}
	}

}
