#include "Window.h"

SE_BEGIN_NAMESPACE

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

ATOM Window::RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, LPCSTR className) {
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = className;
	return RegisterClassEx(&wc);
}

HWND Window::OpenWindow(HINSTANCE hInstance, int cmdShow) {
	ATOM atom = RegisterWindowProc(hInstance, WindowProc, "window");
	if (!atom) {
		return NULL;
	}
	HWND hWnd = CreateWindowEx(NULL, "window", m_title.c_str(), WS_OVERLAPPEDWINDOW, m_x, m_y, m_width, m_height, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, cmdShow);
	return hWnd;
}

void Window::Transform(int width, int height) {
	m_width = width;
	m_height = height;
}

Window::Window(const std::string& title) {
	m_title = title;
	m_width = 800;
	m_height = 500;
	m_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (m_width / 2);
	m_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (m_height / 2);
}

SE_END_NAMESPACE