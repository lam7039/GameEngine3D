#include <iostream>
#include "Engine.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	se::StartEngine("GameEngine3D", hInstance, nCmdShow, 800, 500);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/*
#include <direct.h>
#include <string>
#include <iostream>


std::string current_working_directory()
{
char* cwd = _getcwd(0, 0); // **** microsoft specific ****
std::string working_directory(cwd);
std::free(cwd);
return working_directory;
}

int main() {
std::cout << current_working_directory() << std::endl;

std::cin.get();
return 0;
}
*/