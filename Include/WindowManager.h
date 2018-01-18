#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include "std.h"

namespace se {

	struct WindowEntity {
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
	class WindowManager {
	public:
		WindowManager();
		///
		/// Create a new window
		///
		HWND OpenWindow(const std::string &title, int width, int height);
		///
		/// Returns the active window
		///
		HWND GetActiveWindow();
		///
		/// Get the instance of the window by given index
		///
		HINSTANCE GetInstance(int index);
		///
		/// Get all windows
		///
		std::vector<WindowEntity> GetWindowList() const;
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
		std::vector<WindowEntity> m_windowList;
		ATOM RegisterWindowProc(HINSTANCE hInstance, WNDPROC wndProc, const std::string &className);
	};

}

#endif