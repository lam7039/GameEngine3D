#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <Windows.h>
#include "Vector3.h"

namespace se {



	class Window {
	public:
		Window(int id, std::string title, bool centered, Vector3i position, Vector3i size);
		HWND GetWindowHandle();
		HINSTANCE GetWindowInstanceHandle();
		void SetPosition(int x, int y);
		void SetSize(int width, int height);
		void CloseWindow();
	private:
		HWND m_hWnd;
		HINSTANCE m_instanceHandle;
		std::string m_title;
		Vector3i m_position;
		Vector3i m_size;
		ATOM RegisterWindowProc(HINSTANCE hInstance, const std::string &className);
		static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	};

}

#endif
