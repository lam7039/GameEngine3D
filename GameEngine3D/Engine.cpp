#include "Engine.h"
#include "Display.h"
#include <iostream>

SE_BEGIN_NAMESPACE

HWND hWnd;

void StartEngine(HINSTANCE hInstance, int nCmdShow, std::string title) {
	//initialize logging
	Display window(title);
	hWnd = window.OpenWindow(hInstance, nCmdShow);
}

int EnterLoop(void (*start)(), void (*stop)()) {
	bool isRunning = true;
	start();

	MSG msg;

	while (isRunning) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			isRunning = false;
		}
	}

	stop();

	return msg.wParam;
}

SE_END_NAMESPACE