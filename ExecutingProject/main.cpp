#include <Windows.h>
#include "Engine.h"

void Start() {
	//MessageBox(NULL, "start", "caption", MB_ICONEXCLAMATION | MB_OK);
}

void Stop() {

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	se::StartEngine(hInstance, nCmdShow, "GameEngine3D");
	se::EnterLoop(Start, Stop);

	return 0;
}