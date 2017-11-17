#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"
#include <string>
#include <Windows.h>

SE_BEGIN_NAMESPACE

class Window {
private:
	int _x;
	int _y;
	int _width;
	int _height;
	std::string _title;
	ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, LPCSTR className);
public:
	HWND OpenWindow(HINSTANCE hInstance, int cmdShow);
	void Transform(int width, int height);
	Window(const std::string& title);
};

SE_END_NAMESPACE

#endif