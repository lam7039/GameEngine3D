#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"

SE_BEGIN_NAMESPACE

class Window {
public:
	Window(const std::string& title);
	HWND OpenWindow(HINSTANCE hInstance, int cmdShow);
	void SetSize(int width, int height);
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	std::string m_title;
	ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, LPCSTR className);
};

SE_END_NAMESPACE

#endif