#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <Windows.h>

class Display {
private:
	int x, y, width, height;
	LPCSTR className, title;
	HWND hWnd;
public:
	void RegisterWindow();
	void CreateDisplay(HINSTANCE hInstance, int nCmdShow);
	Display(LPCSTR title, int x, int y, int width, int height);
};

#endif