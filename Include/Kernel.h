#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "Renderer.h"
#include "Input.h"
#include "CameraController.h"
#include "Window.h"

namespace se {

	///
	/// This class is the heart of this engine
	///
	class Kernel {
	public:
		///
		/// Initialize the kernel with the title, width and height of the window, the renderer it's supposed to use and the input it's gonna take
		///
		Kernel(const std::string &title, int width, int height, AbstractRenderer *renderer, Input *input);
		///
		/// Create another window
		///
		void AddWindow(const std::string &title, int width, int height);
		///
		/// Set the CameraController you want to use
		///
		void SetCameraController(CameraController *cameraController);
		///
		/// Enter the gameloop
		///
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