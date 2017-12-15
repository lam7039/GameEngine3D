#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "Renderer.h"

namespace se {

	class Kernel {
	public:
		Kernel(const std::string &title);
		int EnterLoop();
	private:
		HWND m_hWnd;
		AbstractRenderer *m_renderer;
	};

}

#endif