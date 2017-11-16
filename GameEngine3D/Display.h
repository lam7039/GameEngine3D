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
	void RegisterWindow();
public:
	void CreateDisplay(HINSTANCE hInstance, int nCmdShow);
	void Transform(int x, int y, int width, int height);
	Display(std::string title);
};

#endif