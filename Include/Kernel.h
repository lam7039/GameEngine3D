#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"
#include "Window.h"

namespace se {

	class Kernel {
	public:
		Kernel(const std::string &title, int width, int height, AbstractRenderer *renderer);
		void AddWindow(const std::string &title, int width, int height);
		int EnterLoop();
	private:
		Window m_window;
		Input m_input;
		AbstractRenderer *m_renderer;
		Camera m_camera;
		Debug m_logger;
	};

}

#endif