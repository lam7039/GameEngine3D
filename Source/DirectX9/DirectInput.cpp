#include "DirectX9\DirectInput.h"

namespace se {

	DirectInput::DirectInput() {
		m_directInput = nullptr;
		m_keyboard = nullptr;
		m_mouse = nullptr;
		m_logger.SelectLogger("engine.log");
	}

	DirectInput::~DirectInput() {
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

	bool DirectInput::Initialize(HINSTANCE hInstance, HWND hWnd, int screenWidth, int screenHeight) {
		HRESULT result;

		m_screenSize.Set(screenWidth, screenHeight, 0);

		// DirectInput.
		result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
		if (FAILED(result)) {
			return false;
		}

		// Keyboard.
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

		// Mouse.
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

	bool DirectInput::ReadKeyboard() {
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

	bool DirectInput::ReadMouse() {
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

	void DirectInput::Update() {
		bool result;
		result = ReadKeyboard();
		if (!result) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to read keyboard");
		}
		result = ReadMouse();
		if (!result) {
			m_logger.Log(ERRORTYPE_ERROR, __FILE__, __LINE__, "Failed to read mouse");
		}
		ProcessInput();
	}

	void DirectInput::ProcessInput() {
		m_mousePosition.x += m_mouseState.lX;
		m_mousePosition.y += m_mouseState.lY;

		if (m_mousePosition.x < 0) { m_mousePosition.x = 0; }
		if (m_mousePosition.y < 0) { m_mousePosition.y = 0; }

		if (m_mousePosition.x > m_screenSize.x) { m_mousePosition.x = m_screenSize.x; }
		if (m_mousePosition.y > m_screenSize.y) { m_mousePosition.y = m_screenSize.y; }
	}

	bool DirectInput::IsPressed(KeyboardKey key) {
		unsigned char ASCII = MapVirtualKeyEx(key, MAPVK_VK_TO_VSC, GetKeyboardLayout(0));
		switch (key) {
		case SE_KEY_LEFT:
			ASCII = DIK_LEFT;
			break;
		case SE_KEY_RIGHT:
			ASCII = DIK_RIGHT;
			break;
		case SE_KEY_UP:
			ASCII = DIK_UP;
			break;
		case SE_KEY_DOWN:
			ASCII = DIK_DOWN;
			break;
		}
		return (m_keyboardState[ASCII] & 0x80) ? true : false;
	}

	void DirectInput::GetMouseLocation(int &mouseX, int &mouseY) {
		mouseX = m_mousePosition.x;
		mouseY = m_mousePosition.y;
	}

}