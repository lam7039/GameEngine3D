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

	Window::Window(const std::string &title, int width = 800, int height = 500) : m_title(title), m_width(width), m_height(height)
	{
		m_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_width / 2);
		m_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (m_height / 2);
	}

	HWND Window::OpenWindow() {
		m_hInstance = GetModuleHandle(NULL);
		ATOM atom = RegisterWindowProc(m_hInstance, WindowProc, "window");
		if (!atom) {
			return NULL;
		}
		HWND hWnd = CreateWindowEx(NULL, "window", m_title.c_str(), WS_OVERLAPPEDWINDOW, m_x, m_y, m_width, m_height, NULL, NULL, m_hInstance, NULL);
		ShowWindow(hWnd, SW_SHOW);
		return hWnd;
	}

	void Window::SetSize(int width, int height) {
		m_width = width;
		m_height = height;
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
		return m_hInstance;
	}

}