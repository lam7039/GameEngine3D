#ifndef INPUT_H
#define INPUT_H

#include "std.h"
#include "Debug.h"
#include <Windows.h>
#include <dinput.h>

namespace se {

	class Input {
	public:
		Input();
		~Input();

		bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight);
		bool IsPressed(BYTE key);
		void Update();
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