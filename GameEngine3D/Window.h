#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"

BEGIN_NAMESPACE

class Window {
public:
	Window(const std::string& title);
	HWND OpenWindow(const HINSTANCE &hInstance, const int &cmdShow);
	void SetSize(int width, int height);
private:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	std::string m_title;
	ATOM RegisterWindowProc(const HINSTANCE &hInstance, const WNDPROC &wndProc, const std::string &className);
};

END_NAMESPACE

#endif