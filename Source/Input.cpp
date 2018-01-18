#include "Input.h"

namespace se {

	Input::Input() {
		m_directInput = nullptr;
		m_keyboard = nullptr;
		m_mouse = nullptr;
		m_logger.SelectLogger("engine.log");
	}

	Input::~Input() {
		if (m_mouse) {
			m_mouse->Unacquire();
			m_mouse->Release();
			m_mouse = nullptr;
		}
		if (m_keyboard) {
			m_keyboard->Unacquire();
			m_keyboard->Release();
			m_keyboard = nullptr;
		}
		if (m_directInput) {
			m_directInput->Release();
			m_directInput = nullptr;
		}
	}

	bool Input::Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight) {
		HRESULT result;

		m_screenWidth = screenWidth;
		m_screenHeight = screenHeight;

		m_mouseX = 0;
		m_mouseY = 0;

		//DirectInput
		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
		if (FAILED(result)) {
			return false;
		}

		//Keyboard
		result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
		if (FAILED(result)) {
			return false;
		}
		result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
		if (FAILED(result)) {
			return false;
		}
		result = m_keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if (FAILED(result)) {
			return false;
		}
		result = m_keyboard->Acquire();
		if (FAILED(result)) {
			return false;
		}

		//Mouse
		result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
		if (FAILED(result)) {
			return false;
		}
		result = m_mouse->SetDataFormat(&c_dfDIMouse);
		if (FAILED(result)) {
			return false;
		}
		result = m_mouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if (FAILED(result)) {
			return false;
		}
		result = m_mouse->Acquire();
		if (FAILED(result)) {
			return false;
		}

		return true;
	}

	bool Input::ReadKeyboard() {
		HRESULT result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
		if (FAILED(result)) {
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
				m_keyboard->Acquire();
			}
			else {
				return false;
			}
		}
		return true;
	}

	bool Input::ReadMouse() {
		HRESULT result = m_mouse->GetDeviceState(sizeof(m_mouseState), (LPVOID)&m_mouseState);
		if (FAILED(result)) {
			if (result == DIERR_INPUTLOST || result == DIERR_NOTACQUIRED) {
				m_mouse->Acquire();
			}
			else {
				return false;
			}
		}
		return true;
	}

	void Input::Update() {
		bool result;
		result = ReadKeyboard();
		if (!result) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to read keyboard");
		}
		result = ReadMouse();
		if (!result) {
			m_logger.Log(2, __FILE__, __LINE__, "Failed to read mouse");
		}
		ProcessInput();
	}

	void Input::ProcessInput() {
		m_mouseX += m_mouseState.lX;
		m_mouseY += m_mouseState.lY;

		if (m_mouseX < 0) { m_mouseX = 0; }
		if (m_mouseY < 0) { m_mouseY = 0; }

		if (m_mouseX > m_screenWidth) { m_mouseX = m_screenWidth; }
		if (m_mouseY > m_screenHeight) { m_mouseY = m_screenHeight; }
	}

	bool Input::IsPressed(BYTE key) {
		return (m_keyboardState[key]) ? true : false;
	}

	void Input::GetMouseLocation(int &mouseX, int &mouseY) {
		mouseX = m_mouseX;
		mouseY = m_mouseY;
	}

}