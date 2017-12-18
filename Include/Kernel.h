#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"

namespace se {

	class Kernel {
	public:
		Kernel(const std::string &title, int width, int height);
		int EnterLoop();
	private:
		HWND m_hWnd;
		Input m_input;
		AbstractRenderer *m_renderer;
		Camera m_camera;
	};

}

#endif