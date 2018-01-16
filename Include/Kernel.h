#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "Renderer.h"
#include "Input.h"
#include "CameraController.h"
#include "Window.h"

namespace se {

	class Kernel {
	public:
		Kernel(const std::string &title, int width, int height, AbstractRenderer *renderer, Input *input);
		void AddWindow(const std::string &title, int width, int height);
		void AddCameraController(CameraController *cameraController);

		int EnterLoop();
	private:
		Window m_window;
		Input *m_input;
		AbstractRenderer *m_renderer;
		CameraController *m_cameraController;
		Debug m_logger;
	};

}

#endif