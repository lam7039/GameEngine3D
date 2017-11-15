#include <Windows.h>
#include "Display.h"

//figure out some programming standards

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Display window("GameEngine3D", 200, 200, 800, 500);
	window.CreateDisplay(hInstance, nCmdShow);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}