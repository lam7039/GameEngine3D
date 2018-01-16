#include <Windows.h>
#include "Window.h"

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

	Window::Window()
	{
		m_windowCount = 0;
	}

	HWND Window::OpenWindow(const std::string &title = "window", int width = 800, int height = 500) {
		WindowHandle wHndl;
		wHndl.title = title;
		wHndl.width = width;
		wHndl.height = height;
		m_instance = GetModuleHandle(NULL);
		m_windowCount++;
		std::string className = "window" + m_windowCount;
		ATOM atom = RegisterWindowProc(m_instance, WindowProc, className.c_str());
		if (!atom) {
			m_windowCount--;
			return NULL;
		}
		wHndl.hWnd = CreateWindowEx(NULL, className.c_str(), wHndl.title.c_str(), WS_OVERLAPPEDWINDOW, wHndl.x, wHndl.y, wHndl.width, wHndl.height, NULL, NULL, m_instance, NULL);
		if (!wHndl.hWnd) {
			m_windowCount--;
			return NULL;
		}
		ShowWindow(wHndl.hWnd, SW_SHOW);
		m_windowList.push_back(wHndl);
		return wHndl.hWnd;
	}

	void Window::SetPosition(int index, int x, int y) {
		if (index >= m_windowList.size()) {
			return;
		}
		m_windowList[index].x = x;
		m_windowList[index].y = y;
		SetWindowPos(m_windowList[index].hWnd, 0, x, y, m_windowList[index].width, m_windowList[index].height, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Window::SetSize(int index, int width, int height) {
		if (index >= m_windowList.size()) {
			return;
		}
		m_windowList[index].width = width;
		m_windowList[index].height = height;
		SetWindowPos(m_windowList[index].hWnd, 0, m_windowList[index].x, m_windowList[index].y, m_windowList[index].width, m_windowList[index].height, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Window::CloseWindow(int index) {
		DestroyWindow(m_windowList[index].hWnd);
		m_windowList.erase(m_windowList.begin() + index);
	}

	void Window::CloseAll() {
		for (int i = 0; i < m_windowList.size(); i++) {
			DestroyWindow(m_windowList[i].hWnd);
		}
		m_windowList.clear();
	}

	ATOM Window::RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, const std::string &className) {
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

	HINSTANCE Window::GetInstance() {
		return m_instance;
	}

	std::vector<WindowHandle> Window::GetWindowList() const {
		return m_windowList;
	}

}