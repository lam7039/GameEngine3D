#include <Windows.h>
#include "Engine.h"
#include "Window.h"
#include "Debug.h"
#include "Direct3D.h"
#include "FPSCounter.h"

SE_BEGIN_NAMESPACE

HWND hWnd;
Debug log;

SE_API void LogDebug(const std::string& message) {
	log.AppendFile(message);
}

SE_API void StartEngine(HINSTANCE hInstance, int nCmdShow, const std::string &title) {
	// Initialize logging. (still thinking of a better way to do logging)

	Window window(title);
	hWnd = window.OpenWindow(hInstance, nCmdShow);
}

SE_API int EnterLoop(const std::function<void()> &start, const std::function<void()> &stop) {
	bool isRunning = true;

	Direct3D d3d(hWnd);

	start();

	MSG msg;
	FPSCounter fps;

	while (isRunning) {
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT) {
			isRunning = false;
		}

		// Logic.
		LogDebug(std::to_string(fps.GetDelta()));
		d3d.Update(fps.GetDelta());

		// Drawing.
		d3d.Render();

		fps.Update();
	}

	stop();

	return msg.wParam;
}

SE_END_NAMESPACE