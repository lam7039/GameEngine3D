#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include <Windows.h>

namespace se {

	class Kernel {
	public:
		void LogDebug(const std::string& message);
		void StartEngine(const std::string &title);
		int EnterLoop(const std::function<void()> &start, const std::function<void()> &stop);
	private:
		HWND m_hWnd;
		Debug m_log;
	};

}

#endif