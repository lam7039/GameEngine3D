#ifndef KERNEL_H
#define KERNEL_H

#include "std.h"
#include "Debug.h"
#include "Renderer.h"
#include "Input.h"
#include "CameraController.h"
#include "WindowManager.h"

namespace se {

	///
	/// This class is the heart of this engine
	///
	class Kernel {
	public:
		///
		/// Initialize the kernel with standard values and the renderer and input it's supposed to use
		///
		Kernel(const std::string &title, int x, int y, int width, int height, AbstractRenderer *renderer, Input *input);
		///
		/// Create another window
		///
		void AddWindow(const std::string &title, int x, int y, int width, int height);
		///
		/// Set the CameraController you want to use
		///
		void SetCameraController(CameraController *cameraController);
		///
		/// Enter the gameloop
		///
		int EnterLoop();
	private:
		WindowManager m_windows;
		Input *m_input;
		AbstractRenderer *m_renderer;
		CameraController *m_cameraController;
		Debug m_logger;
	};

}

#endif