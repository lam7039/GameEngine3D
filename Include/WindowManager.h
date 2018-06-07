#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <string>
#include <vector>
#include "Debug.h"
#include "Window.h"
#include "Renderer.h"
#include "Input.h"

namespace se {

	///
	/// You can use this manager to create one or more windows.
	///
	class WindowManager {
	public:
		///
		/// Get the initiated instance of WindowManager to use its methods.
		///
		static WindowManager *GetInstance();
		///
		/// Get a window from the list with the index.
		///
		Window GetWindow(int index) const;
		///
		/// Get the last window from the list.
		///
		Window GetLastWindow() const;
		///
		/// Create a new window.
		///
		void AddWindow(const std::string &title, bool centered, int x, int y, int width, int height);
		///
		/// Close all created windows.
		///
		void CloseAll();
		///
		/// Returns the amount of created windows.
		///
		int GetWindowCount();
	private:
		static WindowManager *m_instance;
		std::vector<Window> m_windowList;
		Debug m_logger;
		WindowManager();
	};

}

#endif