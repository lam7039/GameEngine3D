#include <Windows.h>
#include "Debug.h"
#include "Kernel.h"
#include "Window.h"
#include "FPSCounter.h"

namespace se {

	Kernel::Kernel(const std::string &title) {
		// Initialize logging. (still thinking of a better way to do logging)
		Debug logger("engine.log");
		logger.Log(0, __FILE__, __LINE__, "Engine started");

		Window window(title);
		m_hWnd = window.OpenWindow();
		m_d3d.Init(m_hWnd);
	}

	int Kernel::EnterLoop() {
		bool isRunning = true;

		MSG msg;
		FPSCounter fps;

		while (isRunning) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (msg.message == WM_QUIT) {
				isRunning = false;
			}

			// Logic.
			m_d3d.Update(fps.GetDelta());

			// Drawing.
			m_d3d.Render();

			fps.Update();
		}

		m_d3d.Destroy();

		return msg.wParam;
	}

}