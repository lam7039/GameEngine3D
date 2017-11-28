#include <Windows.h>
#include "Engine.h"
#include "Window.h"
#include "Debug.h"
#include "Direct3D.h"
#include "FPSCounter.h"
#include "ResourceManager.h"

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
	ResourceManager resources(d3d.GetDevice());
	resources.AddMesh("Assets\\tiger.x");

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
		d3d.Update(fps.GetTimeMilliseconds());

		
		// Drawing.
		d3d.GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);
		d3d.GetDevice()->BeginScene();

		resources.Render();

		d3d.GetDevice()->EndScene();
		d3d.GetDevice()->Present(NULL, NULL, NULL, NULL);

		fps.Update();
	}

	stop();

	return msg.wParam;
}

SE_END_NAMESPACE