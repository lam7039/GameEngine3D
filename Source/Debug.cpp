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
		std::string types[] = { "info", "warning", "error" };
		int size = sizeof(types) / sizeof(types[0]);
		if (id >= size) {
			return;
		}
		if (!m_file.is_open()) {
			m_file.open(m_path, std::ios::app);
		}
		m_file << __DATE__ << " " << __TIME__ << " " << file << " " << line << " [" << types[id] << "] " << message << std::endl;
		m_file.close();
	}

	void Debug::SelectLogger(const std::string &path) {
		m_path = path;
	}

}
