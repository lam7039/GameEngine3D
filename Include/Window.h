#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"

namespace se {

	struct WindowHandle {
		HWND hWnd;
		int width = 800;
		int height = 500;
		int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
		int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
		std::string title = "window";
	};

	class Window {
	public:
		Window();
		HWND OpenWindow(const std::string &title, int width, int height);
		HINSTANCE GetInstance();
		std::vector<WindowHandle> GetWindowList() const;
		void SetPosition(int index, int x, int y);
		void SetSize(int index, int width, int height);
		void CloseWindow(int index);
		void CloseAll();
	private:
		int m_windowCount;
		HINSTANCE m_instance;
		ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, const std::string &className);
		std::vector<WindowHandle> m_windowList;
	};

}

#endif