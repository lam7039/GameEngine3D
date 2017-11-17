#include "Engine.h"
#include "Display.h"

SE_BEGIN_NAMESPACE

void StartEngine(HINSTANCE hInstance, int nCmdShow, std::string title) {
	//initialize logging
	Display window(title);
	HWND hWnd = window.OpenWindow(hInstance, nCmdShow);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return;
}

SE_END_NAMESPACE