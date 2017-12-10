#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "DirectX9/Direct3D.h"
#include <Windows.h>

namespace se {

	class Kernel {
	public:
		void LogDebug(const std::string& message);
		void StartEngine(const std::string &title);
		int EnterLoop();
	private:
		HWND m_hWnd;
		Debug m_log;
		Direct3D m_d3d;
	};

}

#endif