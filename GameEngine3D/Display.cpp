#include "Display.h"

SE_BEGIN_NAMESPACE

std::wstring string_to_wstring(const std::string& text) {
	return std::wstring(text.begin(), text.end());
}

void Display::CreateDisplay(HINSTANCE hInstance, int nCmdShow) {
	hWnd = CreateWindowEx(NULL, string_to_wstring(_className).c_str(), string_to_wstring(_title).c_str(), WS_OVERLAPPEDWINDOW, _x, _y, _width, _height, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		DestroyWindow(hWnd);
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

void Display::RegisterWindow() {
	_className = "window";
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = string_to_wstring(_className).c_str();
	RegisterClassEx(&wc);
}

void Display::Transform(int width, int height) {
	_width = width;
	_height = height;
}

Display::Display(const std::string& title) {
	_title = title;
	_width = 800;
	_height = 500;
	_x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (_width / 2);
	_y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (_height / 2);
	RegisterWindow();
}

SE_END_NAMESPACE