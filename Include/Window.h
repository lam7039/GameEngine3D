#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"

namespace se {

	class Window {
	public:
		Window(const std::string& title);
		HWND OpenWindow();
		void SetSize(int width, int height);
	private:
		int m_x;
		int m_y;
		int m_width;
		int m_height;
		std::string m_title;
		ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, const std::string &className);
	};

}

#endif