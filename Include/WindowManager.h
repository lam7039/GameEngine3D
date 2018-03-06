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
		/// Get a list of all created windows.
		///
		std::vector<Window> GetWindowList() const;
		///
		/// Create a new window, set a renderer and input to the window.
		///
		void AddWindow(AbstractRenderer *renderer, const std::string &title, bool centered, int x, int y, int width, int height, AbstractInput *input);
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