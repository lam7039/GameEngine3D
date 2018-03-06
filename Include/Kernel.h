#ifndef KERNEL_H
#define KERNEL_H

#include <string>
#include "Debug.h"
#include "Renderer.h"
#include "Input.h"
#include "Camera.h"

namespace se {

	///
	/// This class is the heart of this engine
	///
	class Kernel {
	public:
		///
		/// Initialize the kernel with the renderer and input it's supposed to use and creates a window
		///
		Kernel(const std::string &title, bool centered, int x, int y, int width, int height, AbstractRenderer *renderer, AbstractInput *input);
		///
		/// Enter the gameloop
		///
		int EnterLoop();
	private:
		AbstractInput *m_input;
		AbstractRenderer *m_renderer;
		Debug m_logger;
	};

}

#endif