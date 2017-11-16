#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <Windows.h>

class Display {
private:
	int x;
	int y;
	int width;
	int height;
	std::string className;
	std::string title;
	HWND hWnd;
public:
	void RegisterWindow();
	void CreateDisplay(HINSTANCE hInstance, int nCmdShow);
	Display(std::string title, int x, int y, int width, int height);
};

#endif