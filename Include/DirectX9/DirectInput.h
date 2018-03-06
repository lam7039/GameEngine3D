#ifndef DIRECTINPUT_H
#define DIRECTINPUT_H

#include "Debug.h"
#include "Input.h"
#include "Vector3.h"
#include <dinput.h>

namespace se {

	///
	/// You can use this class to handle input with DirectX9.
	///
	class DirectInput : public AbstractInput {
	public:
		DirectInput();
		~DirectInput();

		///
		/// Initialize the input for the given window instance and handle.
		///
		bool Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight) override;
		///
		/// Check if specified KeyboardKey is pressed.
		///
		bool IsPressed(KeyboardKey key) override;
		///
		/// Update the read key/mouse input.
		///
		void Update() override;
		///
		/// Get the mouse location.
		///
		void GetMouseLocation(int &mouseX, int &mouseY) override;

	private:
		Debug m_logger;

		IDirectInput8 *m_directInput;
		IDirectInputDevice8 *m_keyboard;
		IDirectInputDevice8 *m_mouse;

		BYTE m_keyboardState[256];
		DIMOUSESTATE m_mouseState;

		Vector3i m_screenSize;
		Vector3i m_mousePosition;

		bool ReadKeyboard();
		bool ReadMouse();
		void ProcessInput();
	};

}

#endif