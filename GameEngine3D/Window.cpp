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
	HWND hWnd = CreateWindowEx(NULL, "window", _title.c_str(), WS_OVERLAPPEDWINDOW, _x, _y, _width, _height, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, cmdShow);
	return hWnd;
}

void Window::Transform(int width, int height) {
	_width = width;
	_height = height;
}

Window::Window(const std::string& title) {
	_title = title;
	_width = 800;
	_height = 500;
	_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (_width / 2);
	_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (_height / 2);
}

SE_END_NAMESPACE