#ifndef INPUT_H
#define INPUT_H

#include "std.h"
#include "Debug.h"
#include <Windows.h>
#include <dinput.h>

namespace se {

	///
	/// You can use this class to handle input
	///
	class Input {
	public:
		Input();
		~Input();

		///
		/// Initialize the input
		///
		bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight);
		///
		/// Check if specified key is pressed
		///
		bool IsPressed(BYTE key);
		void Update();
		///
		/// Get the mouse location
		///
		void GetMouseLocation(int &mouseX, int &mouseY);

	private:
		Debug m_logger;

		IDirectInput8 *m_directInput;
		IDirectInputDevice8 *m_keyboard;
		IDirectInputDevice8 *m_mouse;

		BYTE m_keyboardState[256];
		DIMOUSESTATE m_mouseState;

		int m_screenWidth;
		int m_screenHeight;
		int m_mouseX;
		int m_mouseY;

		bool ReadKeyboard();
		bool ReadMouse();
		void ProcessInput();
	};

}

#endif