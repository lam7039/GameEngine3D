#include <Windows.h>
#include "Engine.h"
#include "Window.h"
#include "Direct3D.h"

SE_BEGIN_NAMESPACE

HWND hWnd;

void StartEngine(HINSTANCE hInstance, int nCmdShow, std::string title) {
	//initialize logging
	Window window(title);
	hWnd = window.OpenWindow(hInstance, nCmdShow);
}

int EnterLoop(void (*start)(), void (*stop)()) {
	bool isRunning = true;

	Direct3D d3d;
	d3d.Init(hWnd);

	start();

	MSG msg;

	while (isRunning) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		d3d.Render();

		if (msg.message == WM_QUIT) {
			isRunning = false;
		}
	}

	stop();
	d3d.Clean();

	return msg.wParam;
}

SE_END_NAMESPACE