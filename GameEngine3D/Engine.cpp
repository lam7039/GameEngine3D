#include <Windows.h>
#include "Engine.h"
#include "Window.h"
#include "Debug.h"
#include "Direct3D.h"

SE_BEGIN_NAMESPACE

HWND hWnd;
Debug log;

void LogDebug(const std::string& message) {
	log.AppendFile(message);
}

void StartEngine(HINSTANCE hInstance, int nCmdShow, const std::string &title) {
	// Initialize logging. (still thinking of a better way to do logging)

	Window window(title);
	hWnd = window.OpenWindow(hInstance, nCmdShow);
}

int EnterLoop(const std::function<void()> &start, const std::function<void()> &stop) {
	bool isRunning = true;

	Direct3D d3d(hWnd);

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

		// Logic.


		// Drawing.
		d3d.Render();
	}

	stop();

	return msg.wParam;
}

SE_END_NAMESPACE