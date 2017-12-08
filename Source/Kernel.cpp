#include "Debug.h"
#include "Kernel.h"
#include "Window.h"
#include "Direct3D.h"
#include "FPSCounter.h"

namespace se {

	void Kernel::LogDebug(const std::string& message) {
		m_log.AppendFile(message);
	}

	void Kernel::StartEngine(const std::string &title) {
		// Initialize logging. (still thinking of a better way to do logging)

		Window window(title);
		m_hWnd = window.OpenWindow();
	}

	int Kernel::EnterLoop(const std::function<void()> &start, const std::function<void()> &stop) {
		bool isRunning = true;

		Direct3D d3d(m_hWnd);

		start();

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
			d3d.Update(fps.GetDelta());

			// Drawing.
			d3d.Render();

			fps.Update();
		}

		stop();

		return msg.wParam;
	}

}