#include "Debug.h"

namespace se {

	Debug::Debug(const std::string &path) {
		m_path = path;
		if (!m_file.is_open() && !m_file) {
			m_file.open(m_path, std::ios::out);
		}
	}

	Debug::~Debug() {
		if (m_file.is_open()) {
			m_file.close();
		}
	}

	void Debug::Log(int id, const std::string &file, int line, const std::string &message) {
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
		m_file << message << std::endl;
		m_file.close();
	}

	void Debug::SelectLogger(const std::string &path) {
		m_path = path;
	}

}
