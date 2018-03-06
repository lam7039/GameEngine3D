#ifndef INPUT_H
#define INPUT_H

#include "Key.h"
#include <Windows.h>

namespace se {

	///
	/// You can use this interface to create your own input handler.
	///
	class AbstractInput {
	public:
		///
		/// Initialize the input for the given window instance and handle.
		///
		virtual bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight) = 0;
		///
		/// Check if specified KeyboardKey is pressed.
		///
		virtual bool IsPressed(KeyboardKey key) = 0;
		///
		/// Update the read key/mouse input.
		///
		virtual void Update() = 0;
		///
		/// Get the mouse location.
		///
		virtual void GetMouseLocation(int &mouseX, int &mouseY) = 0;
	};

}

#endif