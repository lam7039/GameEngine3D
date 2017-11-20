#include <fstream>
#include "Debug.h"

SE_BEGIN_NAMESPACE

Debug::Debug() {
	m_path = "DebugLog.log";
	std::ofstream file;
	if (!file.is_open()) {
		file.open(m_path, std::ios::out);
	}
}

void Debug::WriteFile(const std::string& source) {
	std::ofstream file(m_path, std::ios::binary);
	if (!file.is_open()) {
		return;
	}
	file << source << std::endl;
}

void Debug::AppendFile(const std::string& source) {
	std::ofstream file(m_path, std::ios::app);
	if (!file.is_open()) {
		return;
	}
	file << source << std::endl;
}

SE_END_NAMESPACE