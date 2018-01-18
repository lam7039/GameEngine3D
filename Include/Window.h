#ifndef WINDOW_H
#define WINDOW_H

#include "std.h"

namespace se {

	struct WindowHandle {
		HWND hWnd;
		HINSTANCE instance;
		int width = 800;
		int height = 500;
		int x = (GetSystemMetrics(SM_CXSCREEN) / 2) - (width / 2);
		int y = (GetSystemMetrics(SM_CYSCREEN) / 2) - (height / 2);
		std::string title = "window";
	};

	///
	/// You can use this to create a window
	///
	class Window {
	public:
		Window();
		///
		/// Create a new window
		///
		HWND OpenWindow(const std::string &title, int width, int height);
		///
		/// Get the instance of the window by given index
		///
		HINSTANCE GetInstance(int index);
		///
		/// Get all windows
		///
		std::vector<WindowHandle> GetWindowList() const;
		///
		/// Set the position of the given window
		///
		void SetPosition(int index, int x, int y);
		///
		/// Set the size of the given window
		///
		void SetSize(int index, int width, int height);
		///
		/// Close a specified window
		///
		void CloseWindow(int index);
		///
		/// Close all windows
		///
		void CloseAll();
		///
		/// Returns the amount of created windows
		///
		int GetWindowCount();
	private:
		int m_windowCount;
		ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, const std::string &className);
		std::vector<WindowHandle> m_windowList;
	};

}

#endif