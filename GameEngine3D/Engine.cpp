#include "Engine.h"
#include "Display.h"

SE_BEGIN_NAMESPACE

void StartEngine(const std::string& title, HINSTANCE hInstance, int nCmdShow, int width, int height) {

	//initialize logging

	Display window(title);
	window.Transform(width, height);
	window.CreateDisplay(hInstance, nCmdShow);
}

SE_END_NAMESPACE