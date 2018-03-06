#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <fstream>

namespace se {

	enum ErrorType {
		ERRORTYPE_INFO,
		ERRORTYPE_WARNING,
		ERRORTYPE_ERROR,
	};

	///
	/// This class writes error messages to files
	///
	class Debug {
	public:
		///
		/// Initialize debug, sets path to a default logger if nothing is given
		///
		Debug(const std::string &path = "default_logger.log");
		~Debug();
		///
		/// Log an error with a warning level (0-2), the file the error is in which is usually given __FILE__, the line which is usually given __LINE__, and the message it's supposed to write
		///
		void Log(ErrorType errorType, const std::string &file, int line, const std::string &message);
		///
		/// Select the file it's supposed to write in
		///
		void SelectLogger(const std::string &path);
	private:
		std::ofstream m_file;
		std::string m_path;
	};

}

#endif
