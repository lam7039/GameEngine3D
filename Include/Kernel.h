#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "DirectX9/Direct3D.h"

namespace se {

	class Kernel {
	public:
		Kernel(const std::string &title);
		int EnterLoop();
	private:
		HWND m_hWnd;
		Direct3D m_d3d;
	};

}

#endif