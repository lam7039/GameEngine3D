#include <Windows.h>
#include "WindowManager.h"

namespace se {

	LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message) {
		case WM_DESTROY:
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	WindowManager::WindowManager()
	{
		m_windowCount = 0;
	}

	HWND WindowManager::OpenWindow(const std::string &title = "window", int width = 800, int height = 500) {
		WindowEntity entity;
		entity.title = title;
		entity.width = width;
		entity.height = height;
		entity.instance = GetModuleHandle(NULL);
		m_windowCount++;
		std::string className = "windowClass" + m_windowCount;
		ATOM atom = RegisterWindowProc(entity.instance, WindowProc, className);
		if (!atom) {
			m_windowCount--;
			return NULL;
		}
		entity.hWnd = CreateWindowEx(NULL, className.c_str(), entity.title.c_str(), WS_OVERLAPPEDWINDOW, entity.x, entity.y, entity.width, entity.height, NULL, NULL, entity.instance, NULL);
		if (!entity.hWnd) {
			m_windowCount--;
			return NULL;
		}
		ShowWindow(entity.hWnd, SW_SHOW);
		m_windowList.push_back(entity);
		return entity.hWnd;
	}

	HWND WindowManager::GetActiveWindow() {
		return GetForegroundWindow();
	}

	void WindowManager::SetPosition(int index, int x, int y) {
		if (index >= m_windowList.size()) {
			return;
		}
		m_windowList[index].x = x;
		m_windowList[index].y = y;
		SetWindowPos(m_windowList[index].hWnd, 0, x, y, m_windowList[index].width, m_windowList[index].height, SWP_NOSIZE | SWP_NOZORDER);
	}

	void WindowManager::SetSize(int index, int width, int height) {
		if (index >= m_windowList.size()) {
			return;
		}
		m_windowList[index].width = width;
		m_windowList[index].height = height;
		SetWindowPos(m_windowList[index].hWnd, 0, m_windowList[index].x, m_windowList[index].y, m_windowList[index].width, m_windowList[index].height, SWP_NOSIZE | SWP_NOZORDER);
	}

	void WindowManager::CloseWindow(int index) {
		if (index >= m_windowList.size()) {
			return;
		}
		DestroyWindow(m_windowList[index].hWnd);
		m_windowList.erase(m_windowList.begin() + index);
		m_windowCount--;
	}

	void WindowManager::CloseAll() {
		for (int i = 0; i < m_windowList.size(); i++) {
			DestroyWindow(m_windowList[i].hWnd);
		}
		m_windowList.clear();
		m_windowCount = 0;
	}

	ATOM WindowManager::RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, const std::string &className) {
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = wndProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = className.c_str();
		return RegisterClassEx(&wc);
	}

	HINSTANCE WindowManager::GetInstance(int index) {
		if (index >= m_windowList.size()) {
			return NULL;
		}
		return m_windowList[index].instance;
	}

	std::vector<WindowEntity> WindowManager::GetWindowList() const {
		return m_windowList;
	}

	int WindowManager::GetWindowCount() {
		return m_windowCount;
	}

}