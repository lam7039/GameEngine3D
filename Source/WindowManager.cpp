#include <Windows.h>
#include "WindowManager.h"

namespace se {

	WindowManager *WindowManager::m_instance = nullptr;

	WindowManager::WindowManager() {
		m_instance = nullptr;
		m_logger.SelectLogger("engine.log");
	}

	WindowManager *WindowManager::GetInstance() {
		if (!m_instance) {
			m_instance = new WindowManager();
		}
		return m_instance;
	}

	Window WindowManager::GetWindow(int index) const {
		return m_windowList[index];
	}

	Window WindowManager::GetLastWindow() const {
		return m_windowList.back();
	}

	int WindowManager::GetWindowCount() {
		return m_windowList.size();
	}

	void WindowManager::AddWindow(const std::string &title, bool centered, int x, int y, int width, int height) {
		HWND hWnd;
		Window window(m_windowList.size(), title, centered, Vector3i(x, y, 0), Vector3i(width, height, 0));
		if (FAILED(hWnd = window.GetWindowHandle())) {
			m_logger.Log(ERRORTYPE_INFO, __FILE__, __LINE__, "Failed to create window");
			return;
		}
		m_windowList.push_back(window);
	}

	void WindowManager::AddWindow(const std::string &title, bool centered, int x, int y, int width, int height, AbstractRenderer *renderer, AbstractInput *input) {
		HWND hWnd;
		Window window(m_windowList.size(), title, centered, Vector3i(x, y, 0), Vector3i(width, height, 0));
		if (FAILED(hWnd = window.GetWindowHandle())) {
			m_logger.Log(ERRORTYPE_INFO, __FILE__, __LINE__, "Failed to create window");
			return;
		}
		renderer->Create(hWnd, width, height, true, se::CULL_CCW, false, true, se::FM_SOLID, true);
		input->Initialize(window.GetWindowInstanceHandle(), hWnd, width, height);
		m_windowList.push_back(window);
	}

	void WindowManager::CloseAll() {
		for (int i = 0; i < m_windowList.size(); i++) {
			DestroyWindow(m_windowList[i].GetWindowHandle());
		}
		m_windowList.clear();
	}
}