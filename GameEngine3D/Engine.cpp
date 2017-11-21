#include <Windows.h>
#include "Engine.h"
#include "Window.h"
#include "Debug.h"
#include "Direct3D.h"

BEGIN_NAMESPACE

HWND hWnd;
Debug log;

void LogDebug(const std::string& message) {
	log.AppendFile(message);
}

void StartEngine(const HINSTANCE &hInstance, const int &nCmdShow, const std::string &title) {
	// Initialize logging. (still thinking of a better way to do logging)

	Window window(title);
	hWnd = window.OpenWindow(hInstance, nCmdShow);
}

int EnterLoop(void(*start)(), void(*stop)()) {
	bool isRunning = true;

	Direct3D d3d(hWnd);

	start();

	MSG msg;

	while (isRunning) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Logic.


		// Drawing.
		d3d.Draw();

		if (msg.message == WM_QUIT) {
			isRunning = false;
		}
	}

	stop();

	return msg.wParam;
}

END_NAMESPACE