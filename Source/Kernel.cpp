#include <iostream>
#include "Debug.h"
#include "Kernel.h"
#include "Window.h"
#include "FPSCounter.h"
#include "SceneManager.h"
#include "DirectX9\Direct3D.h"

namespace se {

	Kernel::Kernel(const std::string &title, int width, int height) {
		m_logger.SelectLogger("engine.log");
		m_logger.Log(0, __FILE__, __LINE__, "Engine started");

		Window window(title, width, height);
		m_hWnd = window.OpenWindow();

		m_input.Initialize(window.GetInstance(), m_hWnd, width, height);

		m_renderer = new Direct3D();
		m_renderer->Create(m_hWnd);
	}

	int Kernel::EnterLoop() {
		bool isRunning = true;

		MSG msg;
		FPSCounter fps;

		m_logger.Log(0, __FILE__, __LINE__, "Loop entered");
		while (isRunning) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			m_input.Update();

			if (msg.message == WM_QUIT || m_input.IsPressed(DIK_ESCAPE)) {
				isRunning = false;
			}
			m_camera.HandleInput(&m_input, fps.GetDelta());

			// Logic.
			m_camera.Update(fps.GetDelta());
			SceneManager::GetInstance()->GetCurrentScene()->Update(fps.GetDelta());

			// Drawing.
			//TODO: don't render when out of farplane
			m_renderer->Render();

			std::cout << fps.GetFPS() << std::endl;
			fps.Update();
		}

		m_renderer->Release();

		return msg.wParam;
	}

}