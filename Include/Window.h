#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <Windows.h>
#include "Vector3.h"

namespace se {

	class Window {
	public:
		///
		/// Create and show the window.
		///
		Window(int id, std::string title, bool centered, Vector3i position, Vector3i size);
		///
		/// Get the window handle of the window.
		///
		HWND GetWindowHandle();
		///
		/// Get the instance handle of the window.
		///
		HINSTANCE GetWindowInstanceHandle();
		///
		/// Set the position of the window.
		///
		void SetPosition(int x, int y);
		///
		/// Set the size of the window.
		///
		void SetSize(int width, int height);
		///
		/// Close and destroy the window.
		///
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
