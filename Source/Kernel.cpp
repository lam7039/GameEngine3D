#include <iostream>
#include "Debug.h"
#include "Kernel.h"
#include "FPSCounter.h"
#include "SceneManager.h"

namespace se {

	Kernel::Kernel(const std::string &title, int width, int height, AbstractRenderer *renderer, Input *input) {
		m_renderer = nullptr;
		m_cameraController = nullptr;

		m_logger.SelectLogger("engine.log");

		HWND hWnd;
		if (FAILED(hWnd = m_window.OpenWindow(title, width, height))) {
			m_logger.Log(0, __FILE__, __LINE__, "Failed to create window");
			return;
		}

		m_input = input;
		if (!m_input->Initialize(m_window.GetInstance(0), hWnd, width, height)) {
			m_logger.Log(1, __FILE__, __LINE__, "Failed to initialize input");
			return;
		}

		if (!renderer) {
			m_logger.Log(2, __FILE__, __LINE__, "No renderer set");
			return;
		}
		m_renderer = renderer;
		m_renderer->Create(hWnd);

	}

	void Kernel::AddWindow(const std::string &title, int x, int y, int width, int height) {
		HWND hWnd;
		if (FAILED(hWnd = m_window.OpenWindow(title, width, height))) {
			m_logger.Log(0, __FILE__, __LINE__, "Failed to create new window");
			return;
		}
		int index = m_window.GetWindowCount() - 1;
		m_window.SetPosition(index, x, y);
		m_input->Initialize(m_window.GetInstance(index), hWnd, width, height);
	}

	void Kernel::SetCameraController(CameraController *cameraController) {
		m_cameraController = cameraController;
	}

	int Kernel::EnterLoop() {
		if (!m_renderer) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to initialize renderer");
			if (SceneManager::GetInstance()->GetSceneCount() > 0) {
				SceneManager::GetInstance()->RemoveAll();
			}
			m_window.CloseAll();
			return 1;
		}

		bool isRunning = true;

		MSG msg;
		FPSCounter fps;

		while (isRunning) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			m_input->Update();

			if (msg.message == WM_QUIT || m_input->IsPressed(DIK_ESCAPE)) {
				isRunning = false;
			}

			// Logic.
			if (m_cameraController) {
				m_cameraController->HandleInput(fps.GetDelta());
			}
			if (SceneManager::GetInstance()->GetSceneCount() > 0) {
				SceneManager::GetInstance()->GetCurrentScene()->Update(fps.GetDelta());
				if (m_cameraController) {
					SceneManager::GetInstance()->GetCurrentScene()->SetSkyboxTransform(m_cameraController->GetTarget());
				}
			}

			// Drawing.
			for (int i = 0; i < m_window.GetWindowList().size(); i++) {
				m_renderer->Render(m_window.GetWindowList()[i].hWnd);
			}

			fps.Update();
		}

		if (SceneManager::GetInstance()->GetSceneCount() > 0) {
			SceneManager::GetInstance()->RemoveAll();
		}
		m_renderer->Release();
		m_window.CloseAll();

		return msg.wParam;
	}

}