#ifndef INPUT_H
#define INPUT_H

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "std.h"
#include <Windows.h>
#include <dinput.h>

namespace se {

	class Input {
	public:
		Input();
		~Input();

		bool Initialize(HINSTANCE, HWND, int, int);
		bool Update();
		bool IsPressed(BYTE key);
		void GetMouseLocation(int&, int&);

	private:
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