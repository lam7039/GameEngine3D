#include "Window.h"

namespace se {

	Window::Window(int id, std::string title, bool centered, Vector3i position, Vector3i size) : m_title(title), m_position(position), m_size(size) {
		m_size.x = (size.x > 0) ? size.x : 800;
		m_size.y = (size.y > 0) ? size.y : 500;
		if (centered) {
			m_position.x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_size.x / 2) + position.x;
			m_position.y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (m_size.y / 2) + position.y;
		}
		if (m_title == "") {
			m_title = "window";
		}
		m_instanceHandle = GetModuleHandle(NULL);
		std::string className = "windowClass" + id;
		ATOM atom = RegisterWindowProc(m_instanceHandle, className);
		m_hWnd = CreateWindowEx(NULL, className.c_str(), m_title.c_str(), WS_OVERLAPPEDWINDOW, m_position.x, m_position.y, m_size.x, m_size.y, NULL, NULL, m_instanceHandle, NULL);
		ShowWindow(m_hWnd, SW_SHOW);
	}

	HWND Window::GetWindowHandle() {
		return m_hWnd;
	}

	HINSTANCE Window::GetWindowInstanceHandle() {
		return m_instanceHandle;
	}

	void Window::SetPosition(int x, int y) {
		m_position.x = x;
		m_position.y = y;
		SetWindowPos(m_hWnd, 0, m_position.x, m_position.y, m_size.x, m_size.y, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Window::SetSize(int width, int height) {
		m_size.x = width;
		m_size.y = height;
		SetWindowPos(m_hWnd, 0, m_position.x, m_position.y, m_size.x, m_size.y, SWP_NOSIZE | SWP_NOZORDER);
	}

	void Window::CloseWindow() {
		DestroyWindow(m_hWnd);
	}

	LRESULT CALLBACK Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
		switch (message) {
		case WM_DESTROY:
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			return 0;
		}
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	unsigned short Window::RegisterWindowProc(HINSTANCE hInstance, const std::string &className) {
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WindowProc;
		wc.hInstance = hInstance;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wc.lpszClassName = className.c_str();
		return RegisterClassEx(&wc);
	}

}