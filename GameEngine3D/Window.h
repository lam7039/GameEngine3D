#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"
#include <string>
#include <Windows.h>

SE_BEGIN_NAMESPACE

class Window {
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	std::string m_title;
	ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, LPCSTR className);
public:
	HWND OpenWindow(HINSTANCE hInstance, int cmdShow);
	void Transform(int width, int height);
	Window(const std::string& title);
};

SE_END_NAMESPACE

#endif